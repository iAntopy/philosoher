/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:37:49 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/31 22:23:10 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_usleep(t_philo *ph, ssize_t time)
{
	t_tv	start_t;

	gettimeofday(&start_t, NULL);
	while (!(*ph->death_occured) && (timer_ms(&start_t) < time))
		usleep(1000);
	if (*ph->death_occured)
		return (1);
	return (0);
}

void	*coach_overlooking_steaming_brains(void *plato_p)
{
	t_plato *pt;
	t_philo *ph;
	int		i;
	ssize_t	delta_t;

	printf("Coach : started \n");
	pt = (t_plato *)plato_p;
	while (!pt->death_occured)
	{
		usleep(100);
		i = -1;
		while (++i < pt->np)
		{
			ph = pt->philos + i;
			delta_t = timer_ms(&ph->pasta_t);
//			printf("Coach : timing philo %d. delta_t : %zd\n", ph->nb_id, delta_t);
			if (delta_t > pt->delays[0])
			{
				printf("Coach : WOW philo died\n");
				philo_log_event(ph, PH_DIE);
				pt->death_occured = 1;
				break ;
			}
		}
	}
	return (NULL);
}

void	*philo_living_life(void *philo_p)
{
	t_philo	*ph;
	
	ph = (t_philo *)philo_p;
//	printf("philo %zu : it seemed as life had just begun ...\n", ph->thread_id);
//	philo_print(ph);
	usleep(10 * ph->nb_id);
	gettimeofday(&ph->t0, NULL);
	gettimeofday(&ph->pasta_t, NULL);
	while (!(*(ph->death_occured)))
	{
//		printf("philo %zu : philo looping. meals eaten : %zd\n", ph->thread_id, ph->nb_meals);
		pthread_mutex_lock(ph->left_fork);
		if (philo_log_event(ph, PH_FRK))
		{
			pthread_mutex_unlock(ph->left_fork);
			break ;
		}
		pthread_mutex_lock(ph->right_fork);
		gettimeofday(&ph->pasta_t, NULL);

		philo_log_event(ph, PH_FRK);
		philo_log_event(ph, PH_EAT);
		philo_usleep(ph, ph->delays[1]);
		
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		*ph->death_occured |= (ph->delays[3] && ++ph->nb_meals > ph->delays[3]);

		philo_log_event(ph, PH_SLP);
		philo_usleep(ph, ph->delays[2]);
		philo_log_event(ph, PH_THK);
	}
	*ph->death_occured = 1;
	printf("philo %zu : philo exit. Ready to join.\n", (size_t)ph->thread_id);
	return (NULL);
}
