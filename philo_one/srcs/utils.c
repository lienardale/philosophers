/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:22:31 by alienard          #+#    #+#             */
/*   Updated: 2021/01/27 19:01:39 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_init_philo(t_init all, int ac, char **av)
{
	pthread_mutex_init(&all.philo[all.i].right_fork, NULL);
	if (all.i != 0)
		all.philo[all.i].left_fork = &all.philo[all.i - 1].right_fork;
	else
		all.philo[all.i].left_fork = NULL;
	all.philo[all.i].nb_philo = all.check;
	all.philo[all.i].t_todie = ft_atoi(av[2]);
	all.philo[all.i].t_toeat = ft_atoi(av[3]);
	all.philo[all.i].t_tosleep = ft_atoi(av[4]);
	all.philo[all.i].t_begin = all.time_begin;
	if (ac == 6)
		all.philo[all.i].nb_must_eat = ft_atoi(av[5]);
	else
		all.philo[all.i].nb_must_eat = -1;
	all.philo[all.i].t_last_eat = all.time_begin;
	all.philo[all.i].nb_ate = 0;
	all.philo[all.i].id = all.i + 1;
	all.philo[all.i].alive = &all.alive;
	all.philo[all.i].full = &all.full;
	// ft_output(&all.philo[all.i], "is created");
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
