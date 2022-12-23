/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 03:57:25 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/23 04:19:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_dead(t_philo *ph)
{
	int	death;

	if (ph->is_dead)
		return (1);
	pthread_mutex_lock(&ph->glocks->death);
	death = *ph->death_occured;
	pthread_mutex_unlock(&ph->glocks->death);
	return (death);
}

int	is_someone_dead_check(t_philo *ph)
{
	if (is_someone_dead(ph))
		return (1);
	if (timer_us(&ph->pasta_t) >= ph->lims.t_die)
	{
		philo_log(ph, PH_DIE);
		ph->is_dead = 1;
		pthread_mutex_lock(&ph->glocks->death);
		*ph->death_occured = 1;
		pthread_mutex_unlock(&ph->glocks->death);
		return (1);
	}
	return (0);
}

void	increment_nb_meals(t_philo *ph)
{
	int	sim_over;

	if (ph->is_full)
		return ;
	ph->nb_meals++;
	if (ph->lims.max_meals && (ph->nb_meals >= ph->lims.max_meals))
	{
		ph->is_full = 1;
		pthread_mutex_lock(&ph->glocks->meals);
		*ph->nb_hungry -= 1;
		sim_over = (*ph->nb_hungry == 0);
		pthread_mutex_unlock(&ph->glocks->meals);
		if (sim_over)
		{
			pthread_mutex_lock(&ph->glocks->death);
			*ph->death_occured = 1;
			pthread_mutex_unlock(&ph->glocks->death);
		}
	}
}

void	philo_wait_check(t_philo *ph, ssize_t time)
{
	t_tv	t0;

	gettimeofday(&t0, NULL);
	while (!is_someone_dead_check(ph) && timer_us(&t0) < time)
		usleep(100);
}

int	philo_log(t_philo *ph, int event)
{
	char		ts_str[24];
	int			ts_len;
	const char	*msg;
	int			msg_len;

	ts_len = ft_putnbr_buff(ts_str, timer_us(&ph->start_t) / 1000);
	msg = ph->log_msg[event];
	msg_len = ph->log_msg_len[event];
	pthread_mutex_lock(&ph->glocks->print);
	if (!is_someone_dead(ph))
	{
		write(1, ts_str, ts_len);
		write(1, ph->id, ph->__id_len);
		write(1, msg, msg_len);
	}
	pthread_mutex_unlock(&ph->glocks->print);
	return (0);
}
