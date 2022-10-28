/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:50:28 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/27 18:26:04 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_input_fmt(void)
{
	ft_eprintf("Inputs format: ./philo {nb_philos} {time to die} {time to eat} {time to sleep} [max nb of meals]");
	ft_eprintf("	*{is required}, [is optional], time values in millisecs.");
}

int	repport_parsing_error(void)//int err_code)
{
	ft_eprintf(WHITE_BC"(("RED_BC"___________( "CYAN_C"INVALID INPUTS"RED_BC" )___________"WHITE_BC"))\n"WHITE_C);
	print_input_fmt();
	return (-1);
}

int	repport_malloc_error(void)
{
	ft_eprintf(WHITE_BC"(("RED_BC"___________( "CYAN_C"MALLOC ERROR"RED_BC" )___________"WHITE_BC"))\n"WHITE_C);
	return (-1);
}
