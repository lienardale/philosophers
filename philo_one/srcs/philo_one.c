/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard@student.42.fr <alienard>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:25:52 by alienard          #+#    #+#             */
/*   Updated: 2021/01/27 15:31:20 by alienard@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_all_ate(t_world *philo)
{
	pthread_mutex_lock(philo->output);
	printf("%ld Everyone ate %d times.\n", ft_what_time_is_it()
		- philo->t_begin, philo->nb_must_eat);
	*(philo->alive) = false;
	// pthread_mutex_unlock(philo->state);
}

void	*ft_supervise(void *ptr)
{
	t_world	*philo;
	long now;

	philo = (t_world *)ptr;
	// pthread_detach(philo->sthid);
	while (*(philo->alive))
	{
		if (ft_what_time_is_it() - philo->t_last_eat > philo->t_todie
			&& *(philo->alive))
		{
			*(philo->alive) = false;
			now = ft_what_time_is_it() - philo->t_begin;
			// pthread_mutex_lock(philo->output);
			printf("%ld #%d %s\n", now, philo->id, "has DIED");
			// pthread_mutex_unlock(philo->output);
			// pthread_mutex_destroy(philo->output);
			// pthread_detach(philo->sthid);
			// pthread_mutex_unlock(philo->state);
			// printf("philo|%d| returning from superv\n", philo->id);
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
	// printf("philo|%d| returning from superv\n", philo->id);
	// pthread_detach(philo->thid);
	return (NULL);
}

void	*ft_loop(void *ptr)
{
	t_world		*philo;
	// pthread_t	thid;

	philo = (t_world *)ptr;
	pthread_create(&philo->sthid, NULL, ft_supervise, philo);
	pthread_detach(philo->sthid);
	// pthread_detach(philo->thid);
	// if (!ret)
	// {
	// 	// pthread_detach(philo->thid);
	// 	return (NULL);
	// }
	// pthread_detach(philo->sthid);
	if (philo->id % 2 == 0)
		ft_usleep(philo->t_toeat * 0.9);
	while (*(philo->alive) && (philo->nb_must_eat == -1 || philo->nb_must_eat > philo->nb_ate))
	{
		pthread_mutex_lock(&philo->right_fork);
		ft_output(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		ft_output(philo, "has taken a fork");
		philo->t_last_eat = ft_what_time_is_it();
		ft_output(philo, "is eating");
		ft_usleep(philo->t_toeat);
		philo->nb_ate++;
		ft_output(philo, "is sleeping");
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		ft_usleep(philo->t_tosleep);
		ft_output(philo, "is thinking");
	}
	// printf("philo|%d| returning from loop\n", philo->id);
	// pthread_detach(philo->thid);
	return (NULL);
}

void	philo_one(t_world *philo, int check)
{
	int				i;
	// pthread_t		thid;
	// pthread_mutex_t	state;
	pthread_mutex_t	output;
	pthread_mutex_t	nbeat;

	i = -1;
	// pthread_mutex_init(&state, NULL);
	pthread_mutex_init(&output, NULL);
	// pthread_mutex_lock(&state);
	while (++i < check)
	{
		// philo[i].state = &state;
		philo[i].output = &output;
		philo[i].nbeat = &nbeat;
		pthread_create(&philo[i].thid, NULL, ft_loop, &philo[i]);
		// printf("thread:|%d| created\n",i);
		// pthread_detach(philo[i].thid);
	}
	// pthread_mutex_lock(&state);
	i = -1;
	while (++i < check)
	{
	// 	printf("%d\n", i);
		// printf("thread:|%d| waiting to be joined\n",i);
		pthread_join(philo[i].thid, NULL);
		// printf("thread:|%d| joined\n",i);
		// pthread_join(philo[i].sthid, NULL);
		// pthread_detach(philo[i].sthid);

		// pthread_detach(philo[i].thid);
	}
	i= 0;
	while (i < check)
		pthread_mutex_destroy(&philo[i++].right_fork);
	pthread_mutex_destroy(&output);
	// pthread_mutex_destroy(&state);
	free(philo);
}

int		main(int ac, char **av)
{
	t_init	all;

	if (ft_check_args(ac, av) || ft_atoi(av[1]) == 0)
		return (printf("Invalid.\n"));
	all.check = ft_atoi(av[1]);
	all.philo = malloc(sizeof(t_world) * all.check);
	if (!(all.philo))
		return (printf("Malloc error.\n"));
	all.time_begin = ft_what_time_is_it();
	all.i = -1;
	all.full = 0;
	all.alive = true;
	while (++all.i < all.check)
	{
		ft_init_philo(all, ac, av);
	}
	all.philo[0].left_fork = &all.philo[all.philo[0].nb_philo - 1].right_fork;
	philo_one(all.philo, all.check);
	return (0);
}
