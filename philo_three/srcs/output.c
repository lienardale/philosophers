/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:41:16 by alienard          #+#    #+#             */
/*   Updated: 2021/01/29 17:39:51 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_output(t_world *philo, char *what)
{
	long	now;

	now = ft_what_time_is_it() - philo->t_begin;
	if (*(philo->alive))
	{
		sem_wait(philo->output);
		if (*(philo->alive))
			printf("%ld #%d %s\n", now, philo->id, what);
		sem_post(philo->output);
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

void	ft_wait(t_world *philo)
{
	int		i;
	int		status;
	pid_t	wpid;

	i = 0;
	while (i <= philo->nb_philo)
	{
		wpid = waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 0)
		{
			ft_free_all(philo);
			break ;
		}
		else
			i++;
		if (i == philo->nb_philo)
		{
			ft_all_ate(philo);
			break ;
		}
	}
}

void	ft_free_all(t_world *philo)
{
	sem_close(philo->forks);
	sem_close(philo->lock_forks);
	sem_close(philo->nbeat);
	sem_close(philo->output);
	ft_sem_unlink_all();
}

void	ft_exit_fork(t_world *philo)
{
	if (*(philo->alive) == false)
	{
		ft_free_all(philo);
		exit(0);
	}
	if (philo->nb_ate == philo->nb_must_eat)
	{
		ft_free_all(philo);
		exit(1);
	}
}
