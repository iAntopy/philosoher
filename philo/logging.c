/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:24:43 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/31 04:19:14 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
int	philo_log_event(t_philo *ph, int event, ssize_t timestamp)
{
	t_log	*log;

	if (!ph || timestamp == -1)
	{
		philo_log_event(ph, PH_DIE, ph->time_of_death);
		return (-1);
	}
	log = logs_pop_first(ph->logs_pool, ph->pool_lock);
	if (!log)
		return (-1);
	log->id = ph->id;
	log->timestamp = timestamp;
	log->event = event;
	if (!logs_push_front(ph->logs, log, ph->queue_lock))
		return (-1);
	return (0);
}
*/

int	philo_log_event(t_philo *ph, int event, ssize_t timestamp)
{
	char		ts_str[24];
	int		ts_len;
	const char	*msg;
	int		msg_len;

	if (!ph || timestamp == -1)
	{
		philo_log_event(ph, PH_DIE, ph->time_of_death);
		return (-1);
	}
	ts_len = ft_putnbr_buff(ts_str, timestamp);
	msg = ph->log_msg[event];
	msg_len = ph->log_msg_len[event];
	pthread_mutex_lock(ph->print_lock);
	write(1, ts_str, ts_len);
	write(1, ph->id, ph->__id_len);
	write(1, msg, msg_len);
	pthread_mutex_unlock(ph->print_lock);
	return (0);
}

ssize_t	plato_find_min_print_delay(t_plato *pt)
{
	ssize_t	min;

	if (!pt)
		return (-1);
	min = pt->delays[0];
	if (pt->delays[1] < min)
		min = pt->delays[1];
	if (pt->delays[2] < min)
		min = pt->delays[2];
	return (min);
}
/*
int	plato_print_logs(t_plato *pt)
{
	t_log	*log;

	if (!pt)
		return (-1);
//	printf("plato_print_logs : plato has entered\n");
	while (pt->logs)
	{
		log = logs_pop_last(&pt->logs, &pt->queue_lock);
		printf("[%6zd] %d %s\n", log->timestamp,
			log->id, pt->log_msg[log->event]);
		ft_memclear(log, sizeof(t_log));
		logs_push_back(&pt->logs_pool, log, &pt->pool_lock);
	}
	return (0);
}
*/
