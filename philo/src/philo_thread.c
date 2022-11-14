/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:37:49 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/14 15:34:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_usleep(ssize_t time, ssize_t *t_offset)
{
	t_tv	start_t;

	(void)t_offset;
//	printf("\nusleep entered\n");
	gettimeofday(&start_t, NULL);
//	time -= *t_offset;
//	usleep(time - *t_offset);
//	*t_offset = 0;
//	while (time > 0)
//	{
//		usleep(1000);
//		time -= timer_us(&start_t);
//	}
//	time /= 200;
	while (timer_us(&start_t) < time)
		usleep(200);
//	usleep(time);
//	while (time > 0)
//	{
//		usleep(200);
//		time -= 200;
//	}
//	*t_offset = -time;
//	printf("t_offset : %zd\n", *t_offset);
	return (0);
}

void	*coach_overlooking_steaming_brains(void *plato_p)
{
	t_plato *pt;
	t_philo *ph;
	int		i;
//	ssize_t	delta_t;
	int		nb_over_eaters;

//	printf("Coach : started \n");
	pt = (t_plato *)plato_p;
	nb_over_eaters = 0;
	while (!pt->death_occured && nb_over_eaters < pt->np)
	{
		usleep(1000);
		nb_over_eaters = 0;
		i = -1;
		while (++i < pt->np)
		{
			ph = pt->philos + i;
			if (timer_us(&ph->pasta_t) > pt->t_die)
			{
				printf("Coach : WOW philo died\n");
				philo_log_event(ph, PH_DIE);
				pt->death_occured = 1;
				break ;
			}
			if (ph->nb_meals >= pt->max_meals)
				nb_over_eaters++;
		}
//		printf("Coach : nb over_eaters : %d\n", nb_over_eaters);
	}
	if (nb_over_eaters >= pt->np)
	{
		pt->death_occured = 1;
		printf("Coach : All are obese. Simulation over.\n");
	}
//	printf("Coach : BAILS OUT !\n");
	return (NULL);
}

void	*philo_living_life(void *philo_p)
{
	t_philo	*ph;
	
	ph = (t_philo *)philo_p;
//	printf("philo %zu : it seemed as life had just begun ...\n", ph->thread_id);
//	philo_print(ph);
//	usleep(10 * ph->nb_id);
	gettimeofday(&ph->t0, NULL);
	ph->pasta_t = ph->t0;
//	gettimeofday(&ph->pasta_t, NULL);
	while (!(*(ph->death_occured)))
	{
//		printf("philo %zu : philo looping. meals eaten : %zd\n", ph->thread_id, ph->nb_meals);
		pthread_mutex_lock(ph->left_fork);
		if (philo_log_event(ph, PH_FRK) < 0)
		{
			pthread_mutex_unlock(ph->left_fork);
			break ;
		}
		pthread_mutex_lock(ph->right_fork);
		philo_log_event(ph, PH_FRK);

		philo_log_event(ph, PH_EAT);
		gettimeofday(&ph->pasta_t, NULL);
		philo_usleep(ph->t_eat, &ph->t_offset);
	//	if (!ph->death_occured)
		ph->nb_meals++;
		
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);

		philo_log_event(ph, PH_SLP);
		philo_usleep(ph->t_slp, &ph->t_offset);
		philo_log_event(ph, PH_THK);
	}
//	*ph->death_occured == 1;
	printf("philo %zu : philo exit. Ready to join.\n", (size_t)ph->thread_id);
	return (NULL);
}
