/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:08:39 by alienard          #+#    #+#             */
/*   Updated: 2021/01/29 16:21:10 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_all_ate(t_world *philo)
{
	*(philo->alive) = false;
	printf("%ld Everyone ate %d times.\n", ft_what_time_is_it()
		- philo->t_begin, philo->nb_must_eat);
}

void	*ft_supervise(void *ptr)
{
	t_world	*philo;

	philo = (t_world *)ptr;
	while (*(philo->alive) == true)
	{
		if (ft_what_time_is_it() - philo->t_last_eat > philo->t_todie
			&& *(philo->alive))
		{
			*(philo->alive) = false;
			// sem_wait(philo->output);
			printf("%ld #%d %s\n",
				ft_what_time_is_it() - philo->t_begin,
				philo->id, "has died");
			return (NULL);
		}
		else if (*(philo->alive) && philo->nb_must_eat != -1
			&& philo->nb_ate >= philo->nb_must_eat)
		{
			if (philo->nb_ate == philo->nb_must_eat)
				*(philo->full) += 1;
			if (*(philo->full) == philo[0].nb_philo)
				ft_all_ate(philo);
			return (NULL);
		}
	}
	return (NULL);
}

void	*ft_loop(void *ptr)
{
	t_world		*philo;

	philo = (t_world *)ptr;
	pthread_create(&philo->sthid, NULL, ft_supervise, philo);
	while (*(philo->alive) == true
		&& (philo->nb_must_eat == -1 || philo->nb_must_eat > philo->nb_ate))
	{
		sem_wait(philo->lock_forks);
		sem_wait(philo->forks);
		ft_output(philo, "has taken a fork");
		sem_wait(philo->forks);
		ft_output(philo, "has taken a fork");
		sem_post(philo->lock_forks);
		philo->t_last_eat = ft_what_time_is_it();
		ft_output(philo, "is eating");
		ft_usleep(philo->t_toeat);
		philo->nb_ate++;
		sem_post(philo->forks);
		sem_post(philo->forks);
		ft_output(philo, "is sleeping");
		ft_usleep(philo->t_tosleep);
		ft_output(philo, "is thinking");
	}
	pthread_join(philo->sthid, NULL);
	return (NULL);
}

void	philo_two(t_world *philo, int check)
{
	int				i;

	i = -1;
	while (++i < check)
	{
		ft_create_philos(philo, i);
		pthread_create(&philo[i].thid, NULL, ft_loop, &philo[i]);
	}
	i = -1;
	while (++i < check)
		pthread_join(philo[i].thid, NULL);
	sem_post(philo->lock_forks);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	ft_bzero(void *s, size_t n)
{
	char	*us;
	size_t	i;

	us = (char *)s;
	i = 0;
	while (n > i)
	{
		*us = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	if (!(tab = malloc(size * count)))
		return (0);
	ft_bzero(tab, (count * size));
	return (tab);
}

int		main(int ac, char **av)
{
	t_init	all;

	if (ft_check_args(ac, av) || ft_atoi(av[1]) == 0)
		return (printf("Invalid.\n"));
	memset(&all, '\0', sizeof(t_init));
	all.philo = (t_world *)ft_calloc(ft_atoi(av[1]), sizeof(t_world));
	if (!(all.philo))
		return (printf("Malloc error.\n"));
	ft_sem_unlink_all();
	all.check = ft_atoi(av[1]);
	all.time_begin = ft_what_time_is_it();
	all.i = 0;
	all.full = 0;
	all.alive = true;
	ft_init_philo(all, ac, av);
	philo_two(all.philo, all.check);
	sem_close(all.philo[0].forks);
	sem_close(all.philo[0].lock_forks);
	sem_close(all.philo[0].output);
	ft_sem_unlink_all();
	free(all.philo);
	return (0);
}
