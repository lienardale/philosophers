/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:22:31 by alienard          #+#    #+#             */
/*   Updated: 2021/02/01 15:15:56 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_init_philo(t_init *all, int ac, char **av)
{
	all->philo.forks = sem_open("forks", O_CREAT | O_EXCL, 0700, all->check);
	all->philo.lock_forks = sem_open("lock_forks", O_CREAT | O_EXCL, 0700, 1);
	all->philo.output = sem_open("output", O_CREAT | O_EXCL, 0700, 1);
	all->philo.nb_philo = all->check;
	all->philo.t_todie = ft_atoi(av[2]);
	all->philo.t_toeat = ft_atoi(av[3]);
	all->philo.t_tosleep = ft_atoi(av[4]);
	all->philo.t_begin = all->time_begin;
	if (ac == 6)
		all->philo.nb_must_eat = ft_atoi(av[5]);
	else
		all->philo.nb_must_eat = -1;
	all->philo.t_last_eat = all->time_begin;
	all->philo.nb_ate = 0;
	all->philo.id = 1;
	all->philo.alive = &all->alive;
	all->philo.full = &all->full;
}

int		ft_atoi(char *str)
{
	int	i;
	int	neg;
	int	ret;

	i = 0;
	neg = 1;
	ret = 0;
	while (((9 <= str[i] && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (('0' <= str[i] && str[i] <= '9') && str[i])
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(ret * neg));
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

	begin = ft_what_time_is_it();
	while (ft_what_time_is_it() < begin + length)
		usleep(length);
}

void	ft_sem_unlink_all(void)
{
	sem_unlink("forks");
	sem_unlink("lock_forks");
	sem_unlink("output");
}
