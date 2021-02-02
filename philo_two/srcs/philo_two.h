/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:08:36 by alienard          #+#    #+#             */
/*   Updated: 2021/02/01 19:47:11 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

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
	sem_t			*forks;
	sem_t			*lock_forks;
	sem_t			*output;
	pthread_t		thid;
	pthread_t		sthid;
	int				nb_philo;
	int				t_todie;
	int				t_toeat;
	int				t_tosleep;
	long			t_begin;
	int				nb_must_eat;
	long			t_last_eat;
	int				nb_ate;
	int				id;
	sem_t			*lock_alive;
	bool			*alive;
	int				*full;
}					t_world;

typedef struct		s_init
{
	int		check;
	t_world	*philo;
	int		i;
	long	time_begin;
	int		full;
	bool	alive;
}					t_init;

void				ft_init_philo(t_init all, int c, char **av);
int					ft_check_args(int ac, char **av);
void				ft_output(t_world *philo, char *what);
long				ft_what_time_is_it(void);
void				ft_usleep(int length);
int					ft_atoi(char *str);
void				ft_sem_unlink_all(void);
void				ft_create_philos(t_world *philo, int i);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, size_t n);
void				*ft_all_ate(t_world *philo);

#endif
