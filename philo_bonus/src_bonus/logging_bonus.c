/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:40:09 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/11 23:30:46 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_log_event(t_philo *ph, int event)
{
	char		ts_str[24];
	int			ts_len;
	const char	*msg;
	int			msg_len;

	if (!ph)
		return (-1);
	ts_len = ft_putnbr_buff(ts_str, timer_ms(&ph->t0));
	msg = ph->log_msg[event];
	msg_len = ph->log_msg_len[event];
	sem_wait(ph->print_lock);
	if (!ph->is_dead)
	{
		write(1, ts_str, ts_len);
		write(1, ph->id, ph->__id_len);
		write(1, msg, msg_len);
	}
	sem_post(ph->print_lock);
	return (0);
}
