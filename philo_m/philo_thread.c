/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:37:49 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/30 03:03:40 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_living_life(void *philo_p)
{
	struct timeval	t0;
	ssize_t		pasta_time;
	t_philo		*ph;
	
	ph = (t_philo *)philo_p;
	printf("philo %zu : it seemed as life had just begun ...\n", ph->thread_id);
	philo_print(ph);
	gettimeofday(&t0, NULL);
	while (!(*(ph->death_occured)))
	{
//		printf("philo %zu : philo looping. meals eaten : %zd\n", ph->thread_id, ph->nb_meals);
		if (pthread_mutex_lock(ph->left_fork) != 0
			|| philo_log_event(ph, PH_FRK, timer_ms(ph, &t0, pasta_time)) == -1
			|| pthread_mutex_lock(ph->right_fork) != 0
			|| philo_log_event(ph, PH_FRK, timer_ms(ph, &t0, pasta_time)) == -1)
			break ;
		philo_log_event(ph, PH_EAT, timer_update_ms(ph, &t0, &pasta_time));
		usleep(ph->delays[1] * 1000);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);

		if (++ph->nb_meals > ph->delays[3] && ph->delays[3] != 0)
			break ;

		philo_log_event(ph, PH_SLP, timer_ms(ph, &t0, pasta_time));
		usleep(ph->delays[2] * 1000);
		if (philo_log_event(ph, PH_THK, timer_ms(ph, &t0, pasta_time)) == -1)
			break ;
	}
	*ph->death_occured = 1;
	printf("philo %zu : philo exit. Ready to join.\n", ph->thread_id);
	return (NULL);
}
