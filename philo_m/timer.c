/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:10:46 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/30 03:06:14 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
ssize_t	ft_deltatime_usec(void)
{
	static struct timeval	last_t;
	struct timeval			curr_t;
	ssize_t					delta_t;

	gettimeofday(&curr_t, NULL);
	if (last_t.tv_sec)
	{
		delta_t = (size_t)(curr_t.tv_sec - last_t.tv_sec) * 1000000;
		delta_t += (size_t)(curr_t.tv_usec - last_t.tv_usec);
	}
	else
		delta_t = 0;
	last_t = curr_t;
	return (delta_t);
}
*/
ssize_t	timer_ms(t_philo *ph, struct timeval *t0, ssize_t pasta_time)
{
	struct timeval	curr_t;
	ssize_t		delta_t;
	
	if (!ph || !t0)
	{
		ft_eprintf("timer_ms : missing input args pt or t0 ptrs.\n");
		return (0);
	}
	gettimeofday(&curr_t, NULL);
	delta_t = (ssize_t)(curr_t.tv_sec - t0->tv_sec) * 1000;
	delta_t += (ssize_t)(curr_t.tv_usec - t0->tv_usec) / 1000;
//	printf("timer : philo %d, delta_t since last pasta_time : %zd\n", ph->id, delta_t - pasta_time);
	if (delta_t - pasta_time > ph->delays[0])
	{
		ph->time_of_death = delta_t;
		return (-1);
	}
	return (delta_t);
}

ssize_t	timer_update_ms(t_philo *ph, struct timeval *t0, ssize_t *pasta_time)
{
	struct timeval	curr_t;
	ssize_t		delta_t;
	
	if (!ph || !t0 || !pasta_time)
	{
		ft_eprintf("timer_ms : missing input args pt or t0 ptrs.\n");
		return (0);
	}
	gettimeofday(&curr_t, NULL);
	delta_t = (ssize_t)(curr_t.tv_sec - t0->tv_sec) * 1000;
	delta_t += (ssize_t)(curr_t.tv_usec - t0->tv_usec) / 1000;
	*pasta_time = delta_t;
	return (delta_t);
}
