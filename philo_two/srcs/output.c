/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:41:16 by alienard          #+#    #+#             */
/*   Updated: 2021/02/01 17:20:03 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_output(t_world *philo, char *what)
{
	long	now;

	now = ft_what_time_is_it() - philo->t_begin;
	sem_wait(philo->lock_alive);
	if (*(philo->alive))
	{
		sem_wait(philo->output);
		if (*(philo->alive))
			printf("%ld #%d %s\n", now, philo->id, what);
		sem_post(philo->output);
	}
	sem_post(philo->lock_alive);
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
