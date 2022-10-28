/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:24:43 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/27 23:49:57 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_push_log_to_queue(t_philo *ph, t_log *log)
{
	t_log	*q;

	if (!ph || !log)
		return (-1);
	pthread_mutex_lock(ph->queue_lock);
	if (!ph->logs)
		ph->logs = log;
	else
	{
		q = ph->logs;
		while (q->next)
			q = q->next;
		q->next = log;
	}
	pthread_mutex_unlock(ph->queue_lock);
	return (0);
}

int	philo_log_event(t_philo *ph, char event)
{
	t_log	*log;

	if (!ph || !ft_malloc_p(sizeof(t_log), (void **)&log))
		return (-1);
	log->id = ph->id;
	log->timestamp = ph->cumul_time;
	log->event = event;
	log->next = NULL;
	pthread_mutex_lock(ph->queue_lock);
	if (!ph->logs)
		ph->logs = log;
	else
	{
		q = ph->logs;
		while (q->next)
			q = q->next;
		q->next = log;
	}
	pthread_mutex_unlock(ph->queue_lock);

	return (philo_push_log_to_queue(ph, log))
}

int	plato_print_logs(t_plato *pt)
{
	t_log	*log;

	if (!pt)
		return (-1);
	ptread_mutex_lock(&pt->queue_lock);
	while (pt->logs)
	{
		log = pt->logs;
		printf("[%6zd] %d %s\n", log->timestamp,
			log->id, log_msg[log->event]);
		pt->logs = log->next;
		ft_free_p((void **)&log);
	}
	ptread_mutex_unlock(&pt->queue_lock);
	return (0);
}
