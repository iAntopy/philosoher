/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:18 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/23 04:36:23 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	plato_clear(t_plato *pt, int ret_value)
{
	int	i;

	if (!pt)
		return (ret_value);
	usleep(100000);
	i = -1;
	while (pt->philos && (++i < pt->np))
		if (pt->philos[i].tid)
			pthread_join(pt->philos[i].tid, NULL);
	if (pt->philos)
		free(pt->philos);
	if (pt->forks)
	{
		i = -1;
		while (++i < pt->np)
			pthread_mutex_destroy(pt->forks + i);
		ft_free_p((void **)&pt->forks);
	}
	pthread_mutex_destroy(&pt->glocks.print);
	pthread_mutex_destroy(&pt->glocks.death);
	pthread_mutex_destroy(&pt->glocks.meals);
	return (ret_value);
}

static int	plato_init_mutexes(t_plato *pt)
{
	if (!ft_calloc_p(sizeof(pthread_mutex_t) * pt->total_philos,
			(void **)&pt->forks))
		return (repport_malloc_error());
	if (pthread_mutex_init(&pt->glocks.print, NULL) != 0
		|| pthread_mutex_init(&pt->glocks.death, NULL) != 0
		|| pthread_mutex_init(&pt->glocks.meals, NULL) != 0)
		return (repport_mutex_error());
	pt->np = 0;
	while (pt->np < pt->total_philos)
	{
		if (pthread_mutex_init(pt->forks + pt->np, NULL) != 0)
			return (repport_mutex_error());
		pt->np++;
	}
	return (0);
}

static int	plato_init_philos(t_plato *pt)
{
	t_philo	*philos;
	t_philo	*ph;
	int		i;

	philos = NULL;
	if (!ft_calloc_p(sizeof(t_philo) * pt->np, (void **)&philos))
		return (repport_malloc_error());
	i = -1;
	while (++i < pt->np)
	{
		ph = philos + i;
		ph->death_occured = &pt->death_occured;
		ph->nb_hungry = &pt->nb_hungry;
		ph->nb_id = i;
		ph->__id_len = ft_putnbr_buff(ph->id, i + 1);
		ph->lims = pt->lims;
		ph->log_msg = pt->log_msg;
		ph->log_msg_len = (const int *)pt->log_msg_len;
		ph->forks.left = pt->forks + ((i + (i % 2)) % pt->np);
		ph->forks.right = pt->forks + ((i + !(i % 2)) % pt->np);
		ph->glocks = &pt->glocks;
	}
	pt->philos = philos;
	return (0);
}

static int	plato_init(t_plato *pt, int argc, char **argv)
{
	t_philo	*ph;
	int		i;

	if (!parse_inputs(pt, argc, argv))
		return (repport_parsing_error());
	if (plato_init_mutexes(pt) < 0 || plato_init_philos(pt) < 0)
		return (-1);
	pt->nb_hungry = pt->np;
	i = 0;
	while (i < pt->np)
	{
		ph = pt->philos + i;
		gettimeofday(&ph->start_t, NULL);
		ph->pasta_t = ph->start_t;
		if (pt->np > 1 && pthread_create(&ph->tid, NULL, philo_life_cycle, ph))
			return (repport_thread_init_error());
		else if (pt->np == 1 && pthread_create(&ph->tid, NULL, philo_loner, ph))
			return (repport_thread_init_error());
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	const char	*log_msg[5] = {
		"has taken a fork\n", "is eating\n", "is sleeping\n",
		"is thinking\n", "died\n"};
	t_plato		plato;
	int			i;

	ft_memclear(&plato, sizeof(plato));
	plato.log_msg = log_msg;
	i = -1;
	while (++i < 5)
		plato.log_msg_len[i] = (int)ft_strlen(log_msg[i]);
	if (plato_init(&plato, argc, argv) < 0)
		return (plato_clear(&plato, EXIT_FAILURE));
	return (plato_clear(&plato, EXIT_SUCCESS));
}
