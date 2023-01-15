/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_death.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:25:36 by iamongeo          #+#    #+#             */
/*   Updated: 2023/01/14 18:53:48 by iamongeo         ###   ########.fr       */
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

void	*broadcast_death_event(t_philo *ph, int do_log)
{
	pthread_mutex_lock(&ph->glocks->death);
	*ph->death_occured = 1;
	pthread_mutex_unlock(&ph->glocks->death);
	if (do_log)
	{
		pthread_mutex_lock(&ph->glocks->print);
		printf("%zd %s %s", timer_us(&ph->start_t) / 1000,
			ph->id, ph->log_msg[PH_DIE]);
		pthread_mutex_unlock(&ph->glocks->print);
	}
	return (NULL);
}
