/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_ate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:17:40 by alienard          #+#    #+#             */
/*   Updated: 2021/02/01 18:19:29 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*ft_all_ate(t_world *philo)
{
	if (philo->nb_ate == philo->nb_must_eat)
		*(philo->full) += 1;
	if (*(philo->full) == philo[0].nb_philo)
		*(philo->alive) = false;
	sem_post(philo->lock_alive);
	return (NULL);
}
