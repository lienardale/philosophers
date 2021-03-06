/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:39:11 by alienard          #+#    #+#             */
/*   Updated: 2021/02/01 16:43:30 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
			return (NULL);
		}
		else if (*(philo->alive) && philo->nb_must_eat != -1
			&& philo->nb_ate >= philo->nb_must_eat)
		{
			if (philo->nb_ate == philo->nb_must_eat)
				return (NULL);
		}
	}
	return (NULL);
}

void	ft_loop(t_world *philo)
{
	pthread_create(&philo->thid, NULL, ft_supervise, philo);
	while (*(philo->alive) == true
		&& (philo->nb_must_eat == -1 || philo->nb_must_eat > philo->nb_ate))
	{
		sem_wait(philo->lock_forks);
		sem_wait(philo->forks);
		ft_output(philo, "has taken a fork");
		if (philo->nb_philo <= 1)
			break ;
		sem_wait(philo->forks);
		ft_output(philo, "has taken a fork");
		sem_post(philo->lock_forks);
		ft_output(philo, "is eating");
		ft_usleep(philo->t_toeat);
		philo->t_last_eat = ft_what_time_is_it();
		sem_post(philo->forks);
		sem_post(philo->forks);
		philo->nb_ate++;
		ft_output(philo, "is sleeping");
		ft_usleep(philo->t_tosleep);
		ft_output(philo, "is thinking");
	}
	pthread_join(philo->thid, NULL);
	ft_exit_fork(philo);
}

void	philo_three(t_world *philo, int check)
{
	int		i;

	i = -1;
	philo->pid = malloc(sizeof(pid_t) * philo->nb_philo);
	if (!(philo->pid))
		return ;
	while (++i < check)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == 0)
		{
			philo->id = i + 1;
			ft_loop(philo);
			i = philo->nb_philo;
		}
	}
	ft_wait(philo);
	if (philo->pid)
	{
		i = -1;
		while (++i < philo->nb_philo)
			kill(philo->pid[i], SIGTERM);
		free(philo->pid);
	}
	philo->pid = NULL;
}

int		main(int ac, char **av)
{
	t_init	all;

	if (ft_check_args(ac, av) || ft_atoi(av[1]) == 0)
		return (printf("Invalid.\n"));
	ft_sem_unlink_all();
	all.check = ft_atoi(av[1]);
	all.time_begin = ft_what_time_is_it();
	all.i = 0;
	all.full = 0;
	all.alive = true;
	ft_init_philo(&all, ac, av);
	philo_three(&(all.philo), all.check);
	ft_free_all(&(all.philo));
	return (0);
}
