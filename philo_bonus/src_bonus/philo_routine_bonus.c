/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:18:14 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/14 22:18:20 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_usleep(ssize_t time, pthread_mutex_t *lock)
{
	t_tv	start_t;

	gettimeofday(&start_t, NULL);
	while (timer_us(&start_t, lock) < time)
		usleep(500);
}

void	*death_from_above(void *philo_p)
{
	t_philo	*ph;
	
	ph = (t_philo *)philo_p;
	sem_wait(ph->death_occured);
	ft_eprintf("death_from_above : philo %s gets second degree burn. Ayayay!!\n", ph->id);
	ph->is_dead = 1;
	sem_post(ph->death_occured);
	sem_post(ph->death_occured);
	sem_post(ph->philos_all_full);
	sem_post(ph->philos_all_full);
	return (NULL);
}
/*
void	*philos_bloated(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
	sem_wait(ph->philos_all_full);
	ph->is_dead = 1;
	sem_post(ph->death_occured);
	sem_post(ph->philos_all_full);
	return (NULL);
}
*/

void	*coach_overlooking_steaming_brain(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
	while (!ph->is_dead)
	{
		usleep(500);
		if ((timer_us(&ph->pasta_t, &ph->pasta_lock) > ph->t_die) && !philo_log_event(ph, PH_DIE))
		{
			ft_eprintf("CHILD : Coach sets philo %s as dead \n", ph->id);
			ph->is_dead = 1;
			sem_post(ph->death_occured);
			sem_post(ph->death_occured);
			break ;
		}
		if (!ph->is_full && ph->max_meals && (ph->nb_meals >= ph->max_meals))
		{
			ph->is_full = 1;
			sem_post(ph->philos_all_full);
		}
	}
	return (NULL);
}

void	philo_routine(t_philo *ph)
{
	pthread_t	th[3];

	ft_eprintf("CHILD : routine entered\n");
	if (pthread_create(th, NULL, death_from_above, ph)
//		|| pthread_create(th + 1, NULL, philos_bloated, ph)
		|| pthread_create(th + 2, NULL, coach_overlooking_steaming_brain, ph)
		|| pthread_mutex_init(&ph->pasta_lock, NULL))
		return ;

	ft_eprintf("CHILD : getting timeofday\n");
	gettimeofday(&ph->t0, NULL);
	ph->pasta_t = ph->t0;
	while (!ph->is_dead)
	{
//		printf("philo routine : 1\n");
		sem_wait(ph->forks);
//		printf("philo routine : 2\n");
		philo_log_event(ph, PH_FRK);
//		printf("philo routine : 3\n");
		if (ph->is_dead)
		{
			sem_post(ph->forks);
			break ;
		}
		sem_wait(ph->forks);
//		printf("philo routine : 4\n");
		philo_log_event(ph, PH_FRK);
		philo_log_event(ph, PH_EAT);
//		printf("philo routine : 5\n");
		gettimeofday(&ph->pasta_t, NULL);
		philo_usleep(ph->t_eat, &ph->pasta_lock);
//		printf("philo routine : 6\n");
		sem_post(ph->forks);
		sem_post(ph->forks);
		ph->nb_meals++;
//		gettimeofday(&ph->pasta_t, NULL);
		philo_log_event(ph, PH_SLP);
		philo_usleep(ph->t_slp, &ph->pasta_lock);
		philo_log_event(ph, PH_THK);
	}
//	ft_eprintf("CHILD %s : joining death from above thread\n", ph->id);
	pthread_join((pthread_t)th, NULL);
//	ft_eprintf("CHILD %s : joining philos full thread\n", ph->id);
//	pthread_join((pthread_t)(th + 1), NULL);
//	ft_eprintf("CHILD %s : joining Coach thread\n", ph->id);
	pthread_join((pthread_t)(th + 2), NULL);
	pthread_mutex_destroy(&ph->pasta_lock);
	ft_eprintf("CHILD %s  : all threads joined\n", ph->id);
//	exit(EXIT_SUCCESS);
}
