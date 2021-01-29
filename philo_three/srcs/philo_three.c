/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard@student.42.fr <alienard>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:39:11 by alienard          #+#    #+#             */
/*   Updated: 2021/01/29 15:39:29 by alienard@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_all_ate(t_world *philo)
{
	sem_wait(philo->output);
	printf("%ld Everyone ate %d times.\n", ft_what_time_is_it()
		- philo->t_begin, philo->nb_must_eat);
	ft_free_all(philo);
	// exit(0);
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
			sem_wait(philo->output);
			printf("%ld #%d %s\n",
				ft_what_time_is_it() - philo->t_begin,
				philo->id, "has died");
			// pthread_detach(philo->thid);
			// ft_free_all(philo);
			// printf("exits here\n");
			return (NULL);
			// exit(0);
		}
		else if (*(philo->alive) &&philo->nb_must_eat != -1
			&& philo->nb_ate >= philo->nb_must_eat)
		{
			if (philo->nb_ate == philo->nb_must_eat)
			{
				// ft_free_all(philo);
				// *(philo->alive) = false;
				pthread_detach(philo->thid);
				// ft_free_all(philo);
				// ft_all_ate(philo);
				// exit(1);
				// printf("goes in here\n");
				return (NULL);
			}
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
		sem_wait(philo->forks);
		ft_output(philo, "has taken a fork");
		sem_post(philo->lock_forks);
		philo->t_last_eat = ft_what_time_is_it();
		ft_output(philo, "is eating");
		ft_usleep(philo->t_toeat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		philo->nb_ate++;
		ft_output(philo, "is sleeping");
		ft_usleep(philo->t_tosleep);
		ft_output(philo, "is thinking");
	}
	// printf("waiting to be joined\n");
	pthread_join(philo->thid, NULL);
	// printf("joined\n");
	if (*(philo->alive) == false)
	{
		// printf("goes in 0\n");
		ft_free_all(philo);
		exit(0);
	}
	if (philo->nb_ate == philo->nb_must_eat)
	{
		// printf("goes in 1\n");
		ft_free_all(philo);
		exit(1);
	}
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

void	ft_free_all(t_world *philo)
{
	if (philo->pid)
	{
		free(philo->pid);
		philo->pid = NULL;
	}
	// pthread_join(philo->thid, NULL);
	sem_close(philo->forks);
	sem_close(philo->lock_forks);
	sem_close(philo->nbeat);
	sem_close(philo->output);
	ft_sem_unlink_all();
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
	philo_three(&all.philo, all.check);
	sem_close(all.philo.forks);
	sem_close(all.philo.lock_forks);
	sem_close(all.philo.nbeat);
	sem_close(all.philo.output);
	ft_sem_unlink_all();
	// printf("exits here\n");
	return (0);
}
