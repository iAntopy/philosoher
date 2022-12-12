/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:50:28 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/10 20:36:18 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	repport_malloc_error(void)
{
	ft_eprintf(WHITE_BC"\n\t\t(("RED_BC);
	ft_eprintf("__________( "WHITE_BC"MALLOC ERROR"RED_BC" )__________");
	ft_eprintf(WHITE_BC"))\n\n"WHITE_C);
	return (-1);
}

int	repport_mutex_error(void)
{
	ft_eprintf(WHITE_BC"\n\t\t(("RED_BC);
	ft_eprintf("__________( "WHITE_BC"MUTEX ERROR"RED_BC" )__________");
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
