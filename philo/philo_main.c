/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:18 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/28 00:09:56 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	plato_clear(t_plato *pt, int ret_value)
{
	int	i;

	if (pt->philos)
		ft_free_p((void **)&pt->philos);
	if (pt->forks)
	{
		i = -1;
		while (++i < pt->nb_philos)
			pthread_mutex_destroy(pt->forks[i]);
		ft_free_p((void **)&pt->forks);
	}
	pthread_mutex_destroy(&pt->queue_lock);
	return (ret_value);
}

int	plato_init(t_plato *pt, int argc, char **argv)
{
	int	i;

	if (parse_inputs(plato, argc, argv) < 0)
		return (repport_parsing_error());
	if (!ft_calloc_p(sizeof(t_philo) * ps->np, (void **)&pt->philos)
		|| !ft_malloc_p(sizeof(phtread_mutex_t) * pt->np), (void **)&pt->forks)
		return (repport_malloc_error());
	i = -1;
	while (++i < pt->np)
	{
		pt->forks[i] = PTHREAD_MUTEX_INITIALIZER;
		pt->philos[i].id = i;
		pt->philos[i].delays = pt->delays;
		pt->left_fork = pt->forks + ((i - 1) % pt->np);
		pt->right_fork = pt->forks + i;
		pt->philos[i].ts_last_meal = 0;
	}
	pt->queue_lock = PTHREAD_MUTEX_INITIALIZER;
	return (0);
}

int	main(int argc, char **argv)
{
	static const char	log_msg[5] = {"has taken a fork", "is eating", "is sleeping", "is thinking", "died"};
	t_plato				plato;
	
	ft_memclear(&plato, sizeof(plato));
	plato.log_msg = log_msg;
	if (plato_init(&plato, argc, argv) < 0)
		return (plato_clear(&plato, 1));
	plato_print(&pt);
	return (plato_clear(&plato));
}
