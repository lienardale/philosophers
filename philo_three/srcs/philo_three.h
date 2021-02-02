/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:38:39 by alienard          #+#    #+#             */
/*   Updated: 2021/02/01 16:44:16 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <sys/errno.h>

typedef struct		s_world
{
	pid_t			*pid;
	sem_t			*forks;
	sem_t			*lock_forks;
	sem_t			*output;
	pthread_t		thid;
	pid_t			wpid;
	int				nb_philo;
	int				t_todie;
	int				t_toeat;
	int				t_tosleep;
	long			t_begin;
	int				nb_must_eat;
	long			t_last_eat;
	int				nb_ate;
	int				id;
	bool			*alive;
	int				*full;
}					t_world;

typedef struct		s_init
{
	int		check;
	t_world	philo;
	int		i;
	long	time_begin;
	int		full;
	bool	alive;
}					t_init;

void				ft_init_philo(t_init *all, int ac, char **av);
int					ft_check_args(int ac, char **av);
void				ft_output(t_world *philo, char *what);
long				ft_what_time_is_it(void);
void				ft_usleep(int length);
int					ft_atoi(char *str);
void				ft_sem_unlink_all(void);
void				ft_free_all(t_world *philo);
void				ft_exit_fork(t_world *philo);
void				ft_wait(t_world *philo);

#endif
