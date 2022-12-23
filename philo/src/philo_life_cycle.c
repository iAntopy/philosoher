/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:59:16 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/22 21:50:30 by iamongeo         ###   ########.fr       */
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
//		ft_eprintf("philo %s : dying\n", ph->id);
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
	if (ph->is_full)
		return ;
//	pthread_mutex_lock(ph->plocks.meals);
	ph->nb_meals++;
//	pthread_mutex_unlock(ph->plocks.meals);
	if (ph->lims.max_meals && (ph->nb_meals >= ph->lims.max_meals))
	{
		ph->is_full = 1;
		pthread_mutex_lock(&ph->glocks->meals);
		*ph->nb_full += 1;
		pthread_mutex_unlock(&ph->glocks->meals);
		pthread_mutex_lock(&ph->glocks->death);
		*ph->death_occured = 1;
		pthread_mutex_unlock(&ph->glocks->death);
	}
}

int	philo_wait_check(t_philo *ph, ssize_t time)
{
	t_tv	t0;

	gettimeofday(&t0, NULL);
	while (!is_someone_dead_check(ph) && timer_us(&t0) < time)
		usleep(100);
	return (is_someone_dead(ph));
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

void	*philo_single_life_cycle(void *philo_p)
{
	t_philo	*ph;

	ft_eprintf("SINGLE LIFE CYCLE ACTIVATE !\n");
	ph = (t_philo *)philo_p;
	philo_log(ph, PH_FRK);
	philo_wait_check(ph, ph->lims.t_die);
	philo_log(ph, PH_DIE);
	return (NULL);
}

void	*philo_life_cycle(void *philo_p)
{
	t_philo	*ph;

	ph = (t_philo *)philo_p;
	while (!is_someone_dead(ph))
	{
//		ft_eprintf("philo %s : 1\n", ph->id);
		pthread_mutex_lock(ph->forks.left);
//		ft_eprintf("philo %s : 2\n", ph->id);
		philo_log(ph, PH_FRK);
//		ft_eprintf("philo %s : 3\n", ph->id);
		if (is_someone_dead_check(ph))
		{
			pthread_mutex_unlock(ph->forks.left);
			break ;			
		}
//		ft_eprintf("philo %s : 4\n", ph->id);
		pthread_mutex_lock(ph->forks.right);
//		ft_eprintf("philo %s : 5\n", ph->id);
		philo_log(ph, PH_FRK);
//		ft_eprintf("philo %s : 6\n", ph->id);
		philo_log(ph, PH_EAT);
//		ft_eprintf("philo %s : 7\n", ph->id);
		gettimeofday(&ph->pasta_t, NULL);
		if (philo_wait_check(ph, ph->lims.t_eat) < 0)
			break ;
//		ft_eprintf("philo %s : 8\n", ph->id);
		pthread_mutex_unlock(ph->forks.left);
		pthread_mutex_unlock(ph->forks.right);
		increment_nb_meals(ph);
//		ft_eprintf("philo %s : 9\n", ph->id);
		philo_log(ph, PH_SLP);
//		ft_eprintf("philo %s : 10\n", ph->id);
		if (philo_wait_check(ph, ph->lims.t_slp) < 0)
			break ;
//		ft_eprintf("philo %s : 11\n", ph->id);
		philo_log(ph, PH_THK);		
	}
	return (NULL);
}
