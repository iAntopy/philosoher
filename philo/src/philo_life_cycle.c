/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:59:16 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/23 04:36:51 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loner(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
	philo_log(ph, PH_FRK);
	philo_wait_check(ph, ph->lims.t_die);
	philo_log(ph, PH_DIE);
	return (NULL);
}

void	*philo_life_cycle(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
	while (!is_someone_dead(ph))
	{
		pthread_mutex_lock(ph->forks.left);
		philo_log(ph, PH_FRK);
		if (is_someone_dead_check(ph))
		{
			pthread_mutex_unlock(ph->forks.left);
			break ;
		}
		pthread_mutex_lock(ph->forks.right);
		philo_log(ph, PH_FRK);
		philo_log(ph, PH_EAT);
		gettimeofday(&ph->pasta_t, NULL);
		philo_wait_check(ph, ph->lims.t_eat);
		pthread_mutex_unlock(ph->forks.left);
		pthread_mutex_unlock(ph->forks.right);
		increment_nb_meals(ph);
		philo_log(ph, PH_SLP);
		philo_wait_check(ph, ph->lims.t_slp);
		philo_log(ph, PH_THK);
	}
	return (NULL);
}
