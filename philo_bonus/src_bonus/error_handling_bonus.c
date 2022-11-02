/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:50:28 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/01 21:52:21 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_input_fmt(void)
{
	ft_eprintf("Inputs fmt:\t./philo {nb philos} {time to die}");
	ft_eprintf(" {time to eat} {time to sleep} [max nb of meals]\n");
	ft_eprintf("\t\t*{is required}, [is optional], time values in ms.");
}

int	repport_parsing_error(void)
{
	ft_eprintf(WHITE_BC"\n\t\t(("RED_BC);
	ft_eprintf("__________( "WHITE_BC"INVALID INPUTS"RED_BC" )__________");
	ft_eprintf(WHITE_BC"))\n\n"WHITE_C);
	print_input_fmt();
	return (-1);
}

int	repport_semaphore_error(void)
{
	ft_eprintf(WHITE_BC"\n\t\t(("RED_BC);
	ft_eprintf("__________( "WHITE_BC"SEMAPHORE ERROR"RED_BC" )__________");
	ft_eprintf(WHITE_BC"))\n\n"WHITE_C);
	return (-1);
}

int	repport_fork_error(void)
{
	ft_eprintf(WHITE_BC"\n\t\t(("RED_BC);
	ft_eprintf("__________( "WHITE_BC"FORK ERROR"RED_BC" )__________");
	ft_eprintf(WHITE_BC"))\n\n"WHITE_C);
	return (-1);
}

int	repport_thread_init_error(void)
{
	ft_eprintf(WHITE_BC"\n\t\t(("RED_BC);
	ft_eprintf("__________( "WHITE_BC"THREAD INIT ERROR"RED_BC" )__________");
	ft_eprintf(WHITE_BC"))\n\n"WHITE_C);
	return (-1);
}
