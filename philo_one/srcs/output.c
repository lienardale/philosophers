/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:41:16 by alienard          #+#    #+#             */
/*   Updated: 2021/01/29 17:36:53 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_output(t_world *philo, char *what)
{
	long	now;

	now = ft_what_time_is_it() - philo->t_begin;
	if (*(philo->alive) == true)
	{
		pthread_mutex_lock(philo->output);
		if (*(philo->alive) == true)
			printf("%ld #%d %s\n",
				ft_what_time_is_it() - philo->t_begin, philo->id, what);
		pthread_mutex_unlock(philo->output);
	}
}

int		ft_check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (printf("%d arguments given. ", ac));
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (
					printf("'%c' character (non digit) found in arguments. ",
						av[i][j]));
		}
	}
	return (0);
}
