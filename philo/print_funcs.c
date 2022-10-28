/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:14:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/27 23:35:25 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	plato_print(t_plato *pt)
{
	printf("\n****~~~~~~~~~~~~[ PLATO ]~~~~~~~~~~~****\n");
	printf(" ||	nb philos :		%d %20s ||\n", pt->np, "");
	printf(" ||	time to die :	%zd %20s ||\n", pt->delays[0], "");
	printf(" ||	time to eat :	%zd %20s ||\n", pt->delays[1], "");
	printf(" ||	time to slp :	%zd %20s ||\n", pt->delays[2], "");
	printf(" ||	max meals :		%zd %20s ||\n", pt->delays[3], "");
	printf(" ||	forks ptr :		%p %20s ||\n", pt->forks, "");
	printf(" ||	logs ptr :		%p %20s ||\n", pt->logs, "");
	printf("\n****~~~~~~~~~~~~~~*****~~~~~~~~~~~~~****\n");
}
