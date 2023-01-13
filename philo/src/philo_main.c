/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:18 by iamongeo          #+#    #+#             */
/*   Updated: 2023/01/13 00:13:11 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	plato_clear(t_plato *pt, int ret_value)
{
	int	i;

	i = -1;
	while (pt->philos && (++i < pt->np))
	{
		if (pt->philos[i].tid)
		{
			if (pthread_join(pt->philos[i].tid, NULL))
				ft_eprintf("joining philo FAILED!\n");
			pthread_mutex_destroy(&pt->philos[i].plocks.pasta_t);
			pthread_mutex_destroy(&pt->philos[i].plocks.meals);
		}
		if (pt->forks)
			pthread_mutex_destroy(&pt->forks[i]);
	}
	if (pt->forks)
		ft_free_p((void **)&pt->forks);
	if (pt->philos)
		ft_free_p((void **)&pt->philos);
	pthread_mutex_destroy(&pt->glocks.print);
	pthread_mutex_destroy(&pt->glocks.death);
	return (ret_value);
}

static int	plato_init_philos(t_plato *pt)
{
	t_philo	*ph;
	int		i;

	i = -1;
	while (++i < pt->np)
	{
		ph = pt->philos + i;
		ph->death_occured = &pt->death_occured;
		ph->nb_id = i;
		ph->__id_len = ft_putnbr_buff(ph->id, i + 1);
		printf("philo %d id : %s\n", i + 1, ph->id);
		ph->lims = pt->lims;
		ph->log_msg = pt->log_msg;
		ph->forks.left = pt->forks + i + (i % 2);
		ph->forks.right = pt->forks + ((i + !(i % 2)) % pt->np);
//		ph->forks.left = pt->forks + i;
//		ph->forks.right = pt->forks + ((i + 1) % pt->np);
		ph->glocks = &pt->glocks;
		if (pthread_mutex_init(&ph->plocks.pasta_t, NULL) != 0
			|| pthread_mutex_init(&ph->plocks.meals, NULL) != 0
			|| pthread_mutex_init(ph->forks.left, NULL) != 0)
			return (repport_mutex_error());
	}
	return (0);
}

static int	plato_init(t_plato *pt, t_phfunc thread_func)
{
	t_philo	*ph;
	int		i;

	if (plato_init_philos(pt) < 0)
		return (-1);
	if (pthread_mutex_init(&pt->glocks.print, NULL) != 0
		|| pthread_mutex_init(&pt->glocks.death, NULL) != 0)
		return (repport_mutex_error());
	gettimeofday(&pt->start_t, NULL);
	i = 0;
	while (i < pt->np)
	{
		ph = pt->philos + i;
		ph->start_t = pt->start_t;
		ph->pasta_t = pt->start_t;
		if (pthread_create(&ph->tid, NULL, thread_func, ph) < 0)
			return (repport_thread_init_error());
		usleep(100);
		i++;
	}
	return (0);
}

void	*coaching_philos(t_plato *pt)
{
	int		i;
	t_philo	*ph;
	int		nb_full;

	nb_full = 0;
	while (!pt->lims.max_meals || nb_full < pt->np)
	{
		usleep(200);
		nb_full = 0;
		i = -1;
		while (++i < pt->np)
		{
			ph = pt->philos + i;
			if ((time_since_pasta(ph) > pt->lims.t_die)
				&& !philo_log(ph, PH_DIE))
				return (broadcast_death_event(pt));
			if (check_if_full(ph))
				nb_full++;
		}
	}
	return (broadcast_death_event(pt));
}

int	main(int argc, char **argv)
{
	const char	*log_msg[5] = {"has taken a fork\n", "is eating\n",
		"is sleeping\n", "is thinking\n", "died\n"};
	t_plato		plato;

	ft_memclear(&plato, sizeof(plato));
	plato.log_msg = log_msg;
	if (!parse_inputs(&plato, argc, argv))
		return (repport_parsing_error());
	if (!ft_calloc_p(sizeof(pthread_mutex_t) * plato.np, (void **)&plato.forks)
		|| !ft_calloc_p(sizeof(t_philo) * plato.np, (void **)&plato.philos))
		return (repport_malloc_error());
	if (plato.np == 1 && plato_init(&plato, philo_single_life_cycle) < 0)
		return (plato_clear(&plato, 1));
	else if (plato.np > 1 && plato_init(&plato, philo_life_cycle) < 0)
		return (plato_clear(&plato, 1));
	if (plato.np > 1)
		coaching_philos(&plato);
	return (plato_clear(&plato, EXIT_SUCCESS));
}
