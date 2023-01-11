/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:18 by iamongeo          #+#    #+#             */
/*   Updated: 2023/01/11 06:29:40 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	plato_clear(t_plato *pt, int ret_value)
{
	int	i;

	if (!pt)
		return (ret_value);
//	if (pt->coach)
//		pthread_join(pt->coach, NULL);
	usleep(100000);
//	if (pt->np == 1)
//		pthread_mutex_unlock(&pt->forks[0]);
	ft_eprintf("clear : while philos (%p) && (i < np (%d))\n", pt->philos, pt->np);
	i = -1;
	while (pt->philos && (++i < pt->np))
	{
//		printf("philos[i] : %p, tid : %d\n", pt->philos + i, (int)pt->philos[i].tid);
		if (pt->philos[i].tid)
		{
//			printf("joining philos[i] : %p, tid : %d\n", pt->philos + i, (int)pt->philos[i].tid);
			if (pthread_join(pt->philos[i].tid, NULL))
				printf("joining philo FAILED!\n");
			pthread_mutex_destroy(&pt->philos[i].plocks.pasta_t);
			pthread_mutex_destroy(&pt->philos[i].plocks.meals);
		}
	}
	ft_eprintf("clear : all philos supposed to be joined\n");
//	if (pt->philos)
//		free(pt->philos);
//		ft_free_p((void **)&pt->philos);
	if (pt->forks)
	{
		i = -1;
		while (++i < pt->np)
		{
			pthread_mutex_destroy(pt->forks + i);
//			pthread_mutex_destroy(&pt->plocks[i].pasta_t);
//			pthread_mutex_destroy(&pt->plocks[i].meals);
		}
		ft_free_p((void **)&pt->forks);
//		ft_free_p((void **)&pt->plocks);
	}
//	if (pt->philos)
	ft_free_p((void **)&pt->philos);
	pthread_mutex_destroy(&pt->glocks.print);
	pthread_mutex_destroy(&pt->glocks.death);
	return (ret_value);
}

static int	plato_init_mutexes(t_plato *pt)
{
//	t_philo	*ph;
	int	i;

//	printf("init mutexes : malloc forks\n");
	if (!ft_calloc_p(sizeof(pthread_mutex_t) * pt->np, (void **)&pt->forks))
//		|| !ft_calloc_p(sizeof(t_plocks) * pt->total_philos, (void **)&pt->plocks))
		return (repport_malloc_error());
//	printf("init mutexes : init glocks\n");
	if (pthread_mutex_init(&pt->glocks.print, NULL) != 0
		|| pthread_mutex_init(&pt->glocks.death, NULL) != 0)
		return (repport_mutex_error());
	i = -1;
	while (++i < pt->np)
//	pt->np = 0;
//	while (pt->np < pt->total_philos)
	{
//		ph = pt->philos + i;
//		printf("init mutex philo %d ptr : %p\n", pt->np, ph);
//		printf("init mutex philo %d, plock.pasta_t ptr : %p\n", pt->np, &ph->plocks.pasta_t);
		if (pthread_mutex_init(pt->forks + i, NULL) != 0)
//			|| pthread_mutex_init(&ph->plocks.pasta_t, NULL) != 0
//			|| pthread_mutex_init(&ph->plocks.meals, NULL) != 0)
//			|| pthread_mutex_init(&pt->plocks[pt->np].pasta_t, NULL) != 0
//			|| pthread_mutex_init(&pt->plocks[pt->np].meals, NULL) != 0)
//		{
//			while (--i >= 0)
//			{
//				pthread_mutex_destroy(pt->forks + i);
//				pthread_mutex_destroy(&ph->philos[i].plocks.pasta_t, NULL);
//				pthread_mutex_destroy(&ph->philos[i].plocks.meals, NULL);
//			}
//			ft_free_p((void **)&pt->forks);
			return (repport_mutex_error());
//		}
//		pt->np++;
	}
	return (0);
}

static int	plato_init_philos(t_plato *pt)
{
//	t_philo	*philos;
	t_philo	*ph;
	int		i;

//	philos = NULL;
	if (!ft_calloc_p(sizeof(t_philo) * pt->np, (void **)&pt->philos))
		return (repport_malloc_error());
//	pt->philos = philos;
	i = -1;
	while (++i < pt->np)
	{
		ph = pt->philos + i;
		ph->death_occured = &pt->death_occured;
		ph->nb_id = i;
		ph->__id_len = ft_putnbr_buff(ph->id, i + 1);
		ph->lims = pt->lims;
//		ph->start_t = &pt->start_t;
		ph->log_msg = pt->log_msg;
		ph->log_msg_len = (const int *)pt->log_msg_len;
		ph->forks.left = pt->forks + ((i + (i % 2)) % pt->np);
		ph->forks.right = pt->forks + ((i + !(i % 2)) % pt->np);
		ph->glocks = &pt->glocks;
		if (pthread_mutex_init(&ph->plocks.pasta_t, NULL) != 0
			|| pthread_mutex_init(&ph->plocks.meals, NULL) != 0)
			return (repport_mutex_error());
//		ph->plocks = pt->plocks + i;
//		ph->print_lock = &pt->print_lock;
	}
//	pt->philos = philos;
	return (0);
}

static int	plato_init(t_plato *pt, int argc, char **argv)
{
	t_philo	*ph;
	int		i;

	if (!parse_inputs(pt, argc, argv))
		return (repport_parsing_error());
//	printf("parsing success\n");
	if (plato_init_mutexes(pt) < 0 || plato_init_philos(pt) < 0)
//	if (plato_init_philos(pt) < 0 || plato_init_mutexes(pt) < 0)
		return (-1);
	gettimeofday(&pt->start_t, NULL);
	i = 0;
	while (i < pt->np)
	{
//		printf("philo %d\n\n", i);
		ph = pt->philos + i;
//		gettimeofday(&ph->start_t, NULL);
		ph->start_t = pt->start_t;
//		printf("philo start_t copied\n");
//		pthread_mutex_lock(&ph->plocks.pasta_t);
		ph->pasta_t = pt->start_t;
//		pthread_mutex_unlock(&ph->plocks.pasta_t);
//		printf("philo pasta_t = start_t\n");
		if (pt->np > 1 && pthread_create(&ph->tid, NULL, philo_life_cycle, ph))
			return (repport_thread_init_error());
		else if (pt->np == 1 && pthread_create(&ph->tid, NULL, philo_single_life_cycle, ph))
			return (repport_thread_init_error());
//		printf("philo thread started\n");
//		printf("created thread %d : %d\n", i, (int)ph->tid);
		i++;
	}
//	if (pt->np > 1 && pthread_create(&pt->coach, NULL, coach_start, pt))
//		return (repport_thread_init_error());
	return (0);
}

int	main(int argc, char **argv)
{
	const char	*log_msg[5] = {
		"has taken a fork\n", "is eating\n", "is sleeping\n",
		"is thinking\n", "died\n"};
	t_plato				plato;
	int					i;

	ft_memclear(&plato, sizeof(plato));
	plato.log_msg = log_msg;
	i = 0;
	while (i < 5)
	{
		plato.log_msg_len[i] = (int)ft_strlen(log_msg[i]);
		i++;
	}
	printf("init plato\n");
	if (plato_init(&plato, argc, argv) < 0)
		return (plato_clear(&plato, 1));
	coaching_philos(&plato);
	return (plato_clear(&plato, EXIT_SUCCESS));
}
