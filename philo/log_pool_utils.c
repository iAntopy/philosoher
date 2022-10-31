/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_pool_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:36:30 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/30 00:27:00 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//////// FOR DEBUG PURPOSES ONLY ///////////
int	logs_len(t_log *logs, pthread_mutex_t *lock)
{
	t_log	*l;
	int	len;

	if (!logs)
		return (0);
	if (lock)
		pthread_mutex_lock(lock);
	l = logs->next;
	len = 1;
	while (l != logs)
	{
		l = l->next;
		len++;
	}
	if (lock)
		pthread_mutex_unlock(lock);
	return (len);
}

void	logs_clear(t_log **logs, pthread_mutex_t *lock)
{
	t_log	*log;

//	printf("logs clear : entered\n");
	if (!logs || !(*logs))
		return ;
//	printf("logs clear : checks passed. lock : %p\n", lock);
	if (lock)
		pthread_mutex_lock(lock);
//	printf("logs clear : length of logs (%p) to clear : %d\n", *logs, logs_len(*logs, NULL));
	while (*logs)
	{
//		printf("logs clear : try pop first\n");
		log = logs_pop_first(logs, NULL);
//		printf("logs clear : popped %p, now clearing\n", log);
		ft_free_p((void **)&log);
	}
//	printf("logs clear : while loop over\n");
	if (lock)
		pthread_mutex_unlock(lock);
}

t_log	*logs_push_front(t_log **logs, t_log *new, pthread_mutex_t *lock)
{
	t_log	*fst;

	if (!logs || !new)
		return (NULL);
	if (lock)
		pthread_mutex_lock(lock);
	if (!(*logs))
	{
		new->next = new;
		new->prev = new;
	}
	else
	{
		fst = *logs;
		fst->prev->next = new;
		new->prev = fst->prev;
		new->next = fst;
		fst->prev = new;
	}
	*logs = new;
	if (lock)
		pthread_mutex_unlock(lock);
	return (new);
}

t_log	*logs_push_back(t_log **logs, t_log *new, pthread_mutex_t *lock)
{
	t_log	*fst;

	if (!logs || !new)
		return (NULL);
	if (lock)
		pthread_mutex_lock(lock);
	if (!(*logs))
	{
		*logs = new;
		new->next = new;
		new->prev = new;
	}
	else
	{
		fst = *logs;
		fst->prev->next = new;
		new->prev = fst->prev;
		new->next = fst;
		fst->prev = new;
	}
	if (lock)
		pthread_mutex_unlock(lock);
	return (*logs);
}

t_log	*logs_pop_first(t_log **logs, pthread_mutex_t *lock)
{
	t_log	*fst;

	if (!logs || !(*logs))
		return (NULL);
	if (lock)
		pthread_mutex_lock(lock);
	fst = *logs;
	if (fst->next == fst)
		*logs = NULL;
	else
	{
		fst->next->prev = fst->prev;
		fst->prev->next = fst->next;
		*logs = fst->next;
	}
	fst->next = NULL;
	fst->prev = NULL;
	if (lock)
		pthread_mutex_unlock(lock);
	return (fst);
}

t_log	*logs_pop_last(t_log **logs, pthread_mutex_t *lock)
{
	t_log	*last;

	if (!logs || !(*logs))
		return (NULL);
	if (lock)
		pthread_mutex_lock(lock);
	last = (*logs)->prev;
	if (last->next == last)
		*logs = NULL;
	else
	{
		last->prev->next = last->next;
		last->next->prev = last->prev;

	}
	last->next = NULL;
	last->prev = NULL;
	if (lock)
		pthread_mutex_unlock(lock);
	return (last);
}

int	plato_create_log_pool(t_plato *pt)
{
	int	i;
	t_log	*elem;

	printf("create log pool : entered\n");
	i = -1;
	while (++i < (pt->np * 2))
	{
		printf("create log pool : creating log pool item nb %d\n", i);
		if (!ft_calloc_p(sizeof(t_log), (void **)&elem)
			|| !logs_push_front(&pt->logs_pool, elem, NULL))
		{
			printf("create log pool : log pool malloc made a terrible doo doo\n");
			return (-1);
		}
	}
	return (0);
}
