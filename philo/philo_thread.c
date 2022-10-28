/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:37:49 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/27 19:48:01 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *ph)
{
	
}

int	philo_sleep(t_philo *ph)
{
	
}

void	*philo_thread_start(t_philo *ph)
{
	pause();
	while (1)
	{
		philo_eat(ph);
		philo_sleep(ph);
	}
	return (NULL);
}
