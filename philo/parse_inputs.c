/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:48:15 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/31 05:15:06 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_only_digits(char *str)
{
	while (*str)
		if (!ft_isdigit(*(str++)))
			return (0);
	return (1);
}

int	parse_inputs(t_plato *pt, int argc, char **argv)
{
	if (!pt || !argc || !argv)
		return (-1);
	if (argc < 5)
		return (-1);
	if ((argc < 5) || (argc > 6) || !ft_is_only_digits(argv[1])
		|| !ft_is_only_digits(argv[2]) || !ft_is_only_digits(argv[3])
		|| !ft_is_only_digits(argv[4]))
		return (-1);
	pt->np = ft_atol(argv[1]);
	pt->delays[0] = ft_atol(argv[2]);
	pt->delays[1] = ft_atol(argv[3]);
	pt->delays[2] = ft_atol(argv[4]);
	pt->delays[3] = 0;
	if (argc == 6)
	{
		if (!ft_is_only_digits(argv[5]))
			return (-1);
		pt->delays[3] = ft_atol(argv[5]);
	}
	return (pt->np > 0 && pt->delays[0] >= 0 && pt->delays[1] >= 0
		&& pt->delays[2] >= 0 && pt->delays[3] > 0);
}
