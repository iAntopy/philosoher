/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:38:04 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/01 21:38:12 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

ssize_t	timer_ms(t_tv *t0)
{
	t_tv	curr_t;
	ssize_t	delta_t;
	
	if (!t0)
	{
		ft_eprintf("timer_ms : missing input args pt or t0 ptrs.\n");
		return (0);
	}
	gettimeofday(&curr_t, NULL);
	delta_t = (ssize_t)(curr_t.tv_sec - t0->tv_sec) * 1000;
	delta_t += (ssize_t)(curr_t.tv_usec - t0->tv_usec) / 1000;
//	printf("timer : philo %d, delta_t since last pasta_time : %zd\n", ph->id, delta_t - pasta_time);
	return (delta_t);
}
