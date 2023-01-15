/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:37:49 by iamongeo          #+#    #+#             */
/*   Updated: 2023/01/15 18:36:24 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_log(t_philo *ph, int event)
{
	pthread_mutex_lock(&ph->glocks->print);
	if (!is_someone_dead(ph))
		printf("%zd %s %s", timer_us(&ph->start_t) / 1000,
			ph->id, ph->log_msg[event]);
	pthread_mutex_unlock(&ph->glocks->print);
	return (0);
}

static int	philo_wait_us(ssize_t time)
{
	t_tv	start_t;

	gettimeofday(&start_t, NULL);
	while (timer_us(&start_t) < time)
		usleep(50);
	return (0);
}

int	unlock_all_forks(t_philo *ph)
{
	return (pthread_mutex_unlock(ph->forks.left)
		| pthread_mutex_unlock(ph->forks.right));
}

void	*philo_single_life_cycle(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
	printf("%zd %d %s", timer_us(&ph->start_t) / 1000, 1, ph->log_msg[PH_FRK]);
	philo_wait_us(ph->lims.t_die);
	printf("%zd %d %s", timer_us(&ph->start_t) / 1000, 1, ph->log_msg[PH_DIE]);
	return (NULL);
}

void	*philo_life_cycle(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
	while (!is_someone_dead(ph))
	{
		pthread_mutex_lock(ph->forks.left);
		if (philo_log(ph, PH_FRK) < 0
			&& pthread_mutex_unlock(ph->forks.left))
			break ;
		pthread_mutex_lock(ph->forks.right);
		if ((philo_log(ph, PH_FRK) < 0 || philo_log(ph, PH_EAT) < 0)
			&& unlock_all_forks(ph))
			break ;
		update_pasta_time(ph);
		philo_wait_us(ph->lims.t_eat);
		increment_nb_meals(ph);
		unlock_all_forks(ph);
		if (philo_log(ph, PH_SLP) < 0 || philo_wait_us(ph->lims.t_slp) < 0
			|| philo_log(ph, PH_THK) < 0)
			break ;
	}
	return (NULL);
}
