/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:37:49 by iamongeo          #+#    #+#             */
/*   Updated: 2023/01/11 06:10:29 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_someone_dead(t_philo *ph)
{
	int	res;

	pthread_mutex_lock(&ph->glocks->death);
	res = *ph->death_occured;
//	ft_eprintf("philos : death ? %d\n", res);
	pthread_mutex_unlock(&ph->glocks->death);
	return (res);
}

static void	*broadcast_death_event(t_plato *pt)//t_philo *ph)
{
	pthread_mutex_lock(&pt->glocks.death);
	pt->death_occured = 1;
	pthread_mutex_unlock(&pt->glocks.death);
	return (NULL);
}

static ssize_t	time_since_pasta(t_philo *ph)
{
	ssize_t	dt;

	pthread_mutex_lock(&ph->plocks.pasta_t);
	dt = timer_us(&ph->pasta_t);
	pthread_mutex_unlock(&ph->plocks.pasta_t);
	return (dt);	
}

static void	update_pasta_time(t_philo *ph)
{
	pthread_mutex_lock(&ph->plocks.pasta_t);
	gettimeofday(&ph->pasta_t, NULL);
	pthread_mutex_unlock(&ph->plocks.pasta_t);
}

static void	increment_nb_meals(t_philo *ph)
{
	pthread_mutex_lock(&ph->plocks.meals);
	ph->nb_meals++;
	pthread_mutex_unlock(&ph->plocks.meals);
}

static int	get_nb_meals(t_philo *ph)
{
	int	nb_meals;

	pthread_mutex_lock(&ph->plocks.meals);
	nb_meals = ph->nb_meals;
	pthread_mutex_unlock(&ph->plocks.meals);
	return (nb_meals);
}

int	philo_log(t_philo *ph, int event)
{
	char		ts_str[32];
	int			ts_len;
	const char	*msg;
	int			msg_len;

	if (!ph)
		return (-1);
//	ts_len = ft_putnbr_buff(ts_str, time_since_start(ph) / 1000);
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

static int	philo_wait_us(ssize_t time)
{
	t_tv	start_t;

	gettimeofday(&start_t, NULL);
	while (timer_us(&start_t) < time)
		usleep(200);
	return (0);
}
/*
void	*coach_start(void *plato_p)
{
	t_plato	*pt;
	t_philo	*ph;
	int		nb_bloated;

	pt = (t_plato *)plato_p;
	nb_bloated = 0;
	while (!is_someone_dead(pt->philos) && nb_bloated < pt->np)
//	while (!pt->death_occured && nb_bloated < pt->np)
	{
		usleep(500);
		nb_bloated = 0;
		ph = pt->philos - 1;
		i = -1;
		while (++i < pt->np)
//		while (((++ph) - pt->philos) < pt->np)
		{
			if ((time_since_pasta(ph) > pt->lims.t_die) && !philo_log(ph, PH_DIE))
				return (broadcast_death_event(pt->philos));
//		{
//				pt->death_occured = 1;
//				break ;
//			}
			if (pt->lims.max_meals && (get_nb_meals(ph) >= pt->lims.max_meals))
				nb_bloated++;
		}
	}
	return (broadcast_death_event(pt->philos));
}
*/

void	*coaching_philos(t_plato *pt)
{
	int		i;
	t_philo		*ph;
	int		nb_full;

//	pt = (t_plato *)plato_p;
	nb_full = 0;
	while (nb_full < pt->np)
//	while (!is_someone_dead(pt->philos) && nb_full < pt->np)
//	while (!pt->death_occured && nb_bloated < pt->np)
	{
		usleep(500);
		nb_full = 0;
		i = -1;
		while (++i < pt->np)
		{
			ph = pt->philos + i;
			if ((time_since_pasta(ph) > pt->lims.t_die) && !philo_log(ph, PH_DIE))
				return (broadcast_death_event(pt));
//				return (broadcast_death_event(pt->philos));
			if (pt->lims.max_meals && (get_nb_meals(ph) >= pt->lims.max_meals))
				nb_full++;
		}
	}
	return (broadcast_death_event(pt));
//	return (broadcast_death_event(pt->philos));
}


void	*philo_single_life_cycle(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
	philo_log(ph, PH_FRK);
	philo_wait_us(ph->lims.t_die);
	philo_log(ph, PH_DIE);
	return (NULL);
}

void	*philo_life_cycle(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
//	ft_eprintf("philo %s started\n", ph->id);
	while (!is_someone_dead(ph))
	{
		pthread_mutex_lock(ph->forks.left);
		if (philo_log(ph, PH_FRK) < 0
			&& pthread_mutex_unlock(ph->forks.left))
			break ;
		pthread_mutex_lock(ph->forks.right);
		philo_log(ph, PH_FRK);
		philo_log(ph, PH_EAT);
		update_pasta_time(ph);
		philo_wait_us(ph->lims.t_eat);
		increment_nb_meals(ph);
		pthread_mutex_unlock(ph->forks.left);
		pthread_mutex_unlock(ph->forks.right);
		philo_log(ph, PH_SLP);
		philo_wait_us(ph->lims.t_slp);
		philo_log(ph, PH_THK);
	}
//	ft_eprintf("OUT\n");
	return (NULL);
}
