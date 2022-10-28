/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:48:15 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/27 23:53:52 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_inputs(t_plato *pt, int argc, char **argv)
{
	if (!pt || !argc || !argv)
		return (-1);
	if (argc < 5)
		return (-1);
	if ((argc < 5) || (argc > 6) || !ft_isdigit(argv[1]) || !ft_isdigit(argv[2])
		|| !ft_isdigit(argv[3]) || !ft_isdigit(argv[4]))
		return (-1);
	pt->np = ft_atoi(argv[1]);
	pt->delays[0] = ft_atoi(argv[2]);
	pt->delays[1] = ft_atoi(argv[3]);
	pt->delays[2] = ft_atoi(argv[4]);
	pt->delays[3] = 0;
	if (argc == 6)
	{
		if (!ft_isdigit(argv[5]))
			return (-1);
		pt->delays[3] = ft_atoi(argv[5]);
	}
	return (0);
}
