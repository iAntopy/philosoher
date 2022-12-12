/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:18 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/11 22:55:13 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	plato_clear(t_plato *pt, int ret_value)
{
	int	i;

	if (!pt)
		return (ret_value);
	if (pt->coach)
		pthread_join(pt->coach, NULL);
	usleep(100000);
	if (pt->np == 1)
		pthread_mutex_unlock(pt->forks);
	i = -1;
	while (pt->philos && (++i < pt->np))
		if (pt->philos[i].tid)
			pthread_join(pt->philos[i].tid, NULL);
	if (pt->philos)
		ft_free_p((void **)&pt->philos);
	if (pt->forks)
	{
		i = -1;
		while (++i < pt->np)
			pthread_mutex_destroy(pt->forks + i);
		ft_free_p((void **)&pt->forks);
	}
	pthread_mutex_destroy(&pt->print_lock);
	return (ret_value);
}

static int	plato_malloc_init_mutexes(t_plato *pt)
{
	int				i;

	if (!pt
		|| !ft_calloc_p(sizeof(pthread_mutex_t) * pt->np, (void **)&pt->forks)
		|| pthread_mutex_init(&pt->print_lock, NULL) != 0)
	{
		ft_free_p((void **)&pt->forks);
		return (repport_malloc_error());
	}
	i = -1;
	while (++i < pt->np)
	{
		if (pthread_mutex_init(pt->forks + i, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(pt->forks + i);
			ft_free_p((void **)&pt->forks);
			return (repport_mutex_error());
		}
	}
	return (0);
}

static int	plato_malloc_init_philos(t_plato *pt)
{
	t_philo	*philos;
	t_philo	*ph;
	int		i;

	philos = NULL;
	if (!pt || !ft_calloc_p(sizeof(t_philo) * pt->np, (void **)&philos))
		return (repport_malloc_error());
	i = -1;
	while (++i < pt->np)
	{
		ph = philos + i;
		ph->death_occured = &pt->death_occured;
		ph->nb_id = i;
		ph->__id_len = ft_putnbr_buff(ph->id, i + 1);
		ph->t_eat = pt->t_eat;
		ph->t_slp = pt->t_slp;
		ph->log_msg = pt->log_msg;
		ph->log_msg_len = (const int *)pt->log_msg_len;
		ph->left_fork = pt->forks + ((i + (i % 2)) % pt->np);
		ph->right_fork = pt->forks + ((i + !(i % 2)) % pt->np);
		ph->print_lock = &pt->print_lock;
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
	printf("parsing success\n");
	if (plato_malloc_init_mutexes(pt) < 0 || plato_malloc_init_philos(pt) < 0)
		return (-1);
	i = 0;
	while (i < pt->np)
	{
		ph = pt->philos + i;
		if (pthread_create(&(ph->tid), NULL, philo_living, ph))
			return (repport_thread_init_error());
		i++;
	}
	if (pthread_create(&pt->coach, NULL, coach_overlooking_steaming_brains, pt))
		return (repport_thread_init_error());
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
	if (plato_init(&plato, argc, argv) < 0)
		return (plato_clear(&plato, 1));
	return (plato_clear(&plato, EXIT_SUCCESS));
}
