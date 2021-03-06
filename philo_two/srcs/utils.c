/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:22:31 by alienard          #+#    #+#             */
/*   Updated: 2021/02/01 18:16:44 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_init_philo(t_init all, int ac, char **av)
{
	all.philo[0].forks = sem_open("forks", O_CREAT | O_EXCL, 0700, all.check);
	all.philo[0].lock_forks = sem_open("lock_forks", O_CREAT | O_EXCL, 0700, 1);
	all.philo[0].lock_alive = sem_open("lock_alive", O_CREAT | O_EXCL, 0700, 1);
	all.philo[0].output = sem_open("output", O_CREAT | O_EXCL, 0700, 1);
	all.philo[0].nb_philo = all.check;
	all.philo[0].t_todie = ft_atoi(av[2]);
	all.philo[0].t_toeat = ft_atoi(av[3]);
	all.philo[0].t_tosleep = ft_atoi(av[4]);
	all.philo[0].t_begin = all.time_begin;
	if (ac == 6)
		all.philo[all.i].nb_must_eat = ft_atoi(av[5]);
	else
		all.philo[all.i].nb_must_eat = -1;
	all.philo[0].t_last_eat = all.time_begin;
	all.philo[0].nb_ate = 0;
	all.philo[0].id = 1;
	all.philo[0].alive = &all.alive;
	all.philo[0].full = &all.full;
}

void	ft_create_philos(t_world *philo, int i)
{
	if (i != 0)
	{
		philo[i].output = philo[0].output;
		philo[i].forks = philo[0].forks;
		philo[i].lock_forks = philo[0].lock_forks;
		philo[i].lock_alive = philo[0].lock_alive;
		philo[i].nb_philo = philo[0].nb_philo;
		philo[i].t_todie = philo[0].t_todie;
		philo[i].t_toeat = philo[0].t_toeat;
		philo[i].t_tosleep = philo[0].t_tosleep;
		philo[i].t_begin = ft_what_time_is_it();
		philo[i].nb_must_eat = philo[0].nb_must_eat;
		philo[i].t_last_eat = philo[0].t_begin;
		philo[i].nb_ate = 0;
		philo[i].id = philo[i - 1].id + 1;
		philo[i].alive = philo[0].alive;
		philo[i].full = philo[0].full;
	}
}

long	ft_what_time_is_it(void)
{
	int				time;
	struct timeval	i;

	time = gettimeofday(&i, NULL);
	return (i.tv_sec * 1000 + i.tv_usec / 1000);
}

void	ft_usleep(int length)
{
	long	begin;
	long	tmp;

	begin = ft_what_time_is_it();
	tmp = begin + length;
	while (ft_what_time_is_it() < tmp)
		usleep(length);
}

void	ft_sem_unlink_all(void)
{
	sem_unlink("forks");
	sem_unlink("lock_forks");
	sem_unlink("output");
	sem_unlink("lock_alive");
}
