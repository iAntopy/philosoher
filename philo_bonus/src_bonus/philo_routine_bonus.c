/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:18:14 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/01 22:13:16 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_from_above(void *philo_p)
{
	t_philo	*ph;
	
	ph = (t_philo *)philo_p;
	sem_wait(ph->death_occured);
	ph->is_dead = 1;
	sem_post(ph->death_occured);
	sem_post(ph->death_occured);
	return (NULL);
}

void	*philos_bloated(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
	sem_wait(ph->philos_all_full);
	ph->is_dead = 1;
	sem_post(ph->philos_all_full);
	return (NULL);
}

static int	philo_check_status(t_philo *ph)
{
	if (ph->is_dead)
		return (-1);
	if (timer_ms(&ph->pasta_t) > ph->delays[0])
	{
		ph->is_dead = 1;
		sem_post(ph->death_occured);
		philo_log_event(ph, PH_DIE);
	}
	else if (!ph->is_full && ph->delays[3] && (ph->nb_meals > ph->delays[3]))
	{
		ph->is_full = 1;
		sem_post(ph->philos_all_full);
	}
	return (-ph->is_dead);
}

void	philo_sleep_check(t_philo *ph, ssize_t time)
{
	t_tv	start;

	gettimeofday(&start, NULL);
	while (!philo_check_status(ph) && timer_ms(&start) < time)
		usleep(500);
}

void	philo_routine(t_philo *ph)
{
	pthread_t	th[2];

	if (pthread_create(th, NULL, death_from_above, ph->death_occured)
		|| pthread_create(th + 1, NULL, philos_bloated, ph->philos_all_full))
		return ;
	gettimeofday(&ph->t0, NULL);
	while (!ph->is_dead)
	{
		printf("philo routine : 1\n");
		sem_wait(ph->forks);
		printf("philo routine : 2\n");
		philo_log_event(ph, PH_FRK);
		printf("philo routine : 3\n");
		sem_wait(ph->forks);
		printf("philo routine : 4\n");
		philo_log_event(ph, PH_FRK);
		printf("philo routine : 5\n");
		philo_sleep_check(ph, ph->delays[1]);
		printf("philo routine : 6\n");
		sem_post(ph->forks);
		sem_post(ph->forks);
		ph->nb_meals++;
		gettimeofday(&ph->pasta_t, NULL);
		philo_log_event(ph, PH_SLP);
		philo_sleep_check(ph, ph->delays[2]);
		philo_log_event(ph, PH_THK);
	}
	pthread_join((pthread_t)th, NULL);
	pthread_join((pthread_t)(th + 1), NULL);
	exit(EXIT_SUCCESS);
}
