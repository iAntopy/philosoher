/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:37:49 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/11 23:53:06 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_log(t_philo *ph, int event)
{
	char		ts_str[32];
	int			ts_len;
	const char	*msg;
	int			msg_len;

	if (!ph)
		return (-1);
	ts_len = ft_putnbr_buff(ts_str, timer_us(&ph->t0) / 1000);
	msg = ph->log_msg[event];
	msg_len = ph->log_msg_len[event];
	pthread_mutex_lock(ph->print_lock);
	if (!(*ph->death_occured))
	{
		write(1, ts_str, ts_len);
		write(1, ph->id, ph->__id_len);
		write(1, msg, msg_len);
	}
	pthread_mutex_unlock(ph->print_lock);
	return (0);
}

static int	philo_usleep(ssize_t time)
{
	t_tv	start_t;

	gettimeofday(&start_t, NULL);
	while (timer_us(&start_t) < time)
		usleep(200);
	return (0);
}

void	*coach_overlooking_steaming_brains(void *plato_p)
{
	t_plato	*pt;
	t_philo	*ph;
	int		nb_over_eaters;

	pt = (t_plato *)plato_p;
	nb_over_eaters = 0;
	while (!pt->death_occured && nb_over_eaters < pt->np)
	{
		usleep(500);
		nb_over_eaters = 0;
		ph = pt->philos - 1;
		while (((++ph) - pt->philos) < pt->np)
		{
			if ((timer_us(&ph->pasta_t) > pt->t_die) && !philo_log(ph, PH_DIE))
			{
				pt->death_occured = 1;
				break ;
			}
			if (pt->max_meals && (ph->nb_meals >= pt->max_meals))
				nb_over_eaters++;
		}
	}
	if (nb_over_eaters >= pt->np)
		pt->death_occured = 1;
	return (NULL);
}

void	*philo_living(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
	gettimeofday(&ph->t0, NULL);
	ph->pasta_t = ph->t0;
	while (!(*(ph->death_occured)))
	{
		pthread_mutex_lock(ph->left_fork);
		if (philo_log(ph, PH_FRK) < 0
			&& pthread_mutex_unlock(ph->left_fork))
			break ;
		pthread_mutex_lock(ph->right_fork);
		philo_log(ph, PH_FRK);
		philo_log(ph, PH_EAT);
		gettimeofday(&ph->pasta_t, NULL);
		philo_usleep(ph->t_eat);
		ph->nb_meals++;
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		philo_log(ph, PH_SLP);
		philo_usleep(ph->t_slp);
		philo_log(ph, PH_THK);
	}
	return (NULL);
}
