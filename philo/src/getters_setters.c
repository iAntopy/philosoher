/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:19:32 by iamongeo          #+#    #+#             */
/*   Updated: 2023/01/12 22:27:15 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	time_since_pasta(t_philo *ph)
{
	ssize_t	dt;

	pthread_mutex_lock(&ph->plocks.pasta_t);
	dt = timer_us(&ph->pasta_t);
	pthread_mutex_unlock(&ph->plocks.pasta_t);
	return (dt);
}

void	update_pasta_time(t_philo *ph)
{
	pthread_mutex_lock(&ph->plocks.pasta_t);
	gettimeofday(&ph->pasta_t, NULL);
	pthread_mutex_unlock(&ph->plocks.pasta_t);
}

void	increment_nb_meals(t_philo *ph)
{
	ph->nb_meals++;
	if (ph->nb_meals >= ph->lims.max_meals)
	{
		pthread_mutex_lock(&ph->plocks.meals);
		ph->is_full = 1;
		pthread_mutex_unlock(&ph->plocks.meals);
	}
}

int	check_if_full(t_philo *ph)
{
	int	is_full;

	pthread_mutex_lock(&ph->plocks.meals);
	is_full = ph->is_full;
	pthread_mutex_unlock(&ph->plocks.meals);
	return (is_full);
}
