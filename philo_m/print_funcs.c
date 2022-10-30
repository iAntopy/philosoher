/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:14:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/30 02:16:16 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *ph)
{
	printf("\n¤**¤~~~~~~~~~~~~~~~¤{ PHILO }¤~~~~~~~~~~~~~~¤**¤\n");
	printf(" ||	thread_id :	%20zd ||\n", ph->thread_id);
	printf(" ||	id :		%20d ||\n", ph->id);
	printf(" ||	delays :	%20p ||\n", ph->delays);
	printf(" ||	left_frk :	%20p ||\n", ph->left_fork);
	printf(" ||	right_fork :	%20p ||\n", ph->right_fork);
	printf(" ||	queue_lock :	%20p ||\n", ph->queue_lock);
	printf(" ||	pool_lock :	%20p ||\n", ph->pool_lock);
	printf(" ||	logs ptr :	%20p ||\n", ph->logs);
	printf(" ||	logs pool ptr :	%20p ||\n", ph->logs_pool);
	printf(" ||	time of death :	%20zd ||\n", ph->time_of_death);
	printf(" ||	nb meals :	%20zd ||\n", ph->nb_meals);
	printf("¤°°¤~~~~~~~~~~~~~~~~~°¤*¤*¤°~~~~~~~~~~~~~~~~¤°°¤\n\n");
}

void	plato_print(t_plato *pt)
{
	printf("\n¤**¤~~~~~~~~~~~~~~~¤{ PLATO }¤~~~~~~~~~~~~~~¤**¤\n");
	printf(" ||	nb philos :	%20d ||\n", pt->np);
	printf(" ||	time to die :	%20zd ||\n", pt->delays[0]);
	printf(" ||	time to eat :	%20zd ||\n", pt->delays[1]);
	printf(" ||	time to slp :	%20zd ||\n", pt->delays[2]);
	printf(" ||	max meals :	%20zd ||\n", pt->delays[3]);
	printf(" ||	forks ptr :	%20p ||\n", pt->forks);
	printf(" ||	logs ptr :	%20p ||\n", pt->logs);
	printf(" ||	logs pool ptr :	%20p ||\n", pt->logs_pool);
	printf("¤°°¤~~~~~~~~~~~~~~~~~°¤*¤*¤°~~~~~~~~~~~~~~~~¤°°¤\n\n");
}
