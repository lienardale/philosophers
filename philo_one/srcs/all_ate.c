/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_ate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:55:29 by alienard          #+#    #+#             */
/*   Updated: 2021/02/01 19:56:25 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_all_ate(t_world *philo)
{
	if (philo->nb_ate == philo->nb_must_eat)
		*(philo->full) += 1;
	if (*(philo->full) == philo[0].nb_philo)
		*(philo->alive) = false;
	pthread_mutex_unlock(philo->lock_alive);
	return (NULL);
}
