/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_death.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:25:36 by iamongeo          #+#    #+#             */
/*   Updated: 2023/01/12 22:25:47 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_dead(t_philo *ph)
{
	int	res;

	pthread_mutex_lock(&ph->glocks->death);
	res = *ph->death_occured;
	pthread_mutex_unlock(&ph->glocks->death);
	return (res);
}

void	*broadcast_death_event(t_plato *pt)
{
	pthread_mutex_lock(&pt->glocks.death);
	pt->death_occured = 1;
	pthread_mutex_unlock(&pt->glocks.death);
	return (NULL);
}
