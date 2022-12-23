/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:48:15 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/23 05:12:02 by iamongeo         ###   ########.fr       */
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
	if (!pt || !argc || !argv || argc < 5 || argc > 6)
		return (0);
	if (!ft_is_only_digits(argv[1]) || !ft_is_only_digits(argv[2])
		|| !ft_is_only_digits(argv[3]) || !ft_is_only_digits(argv[4]))
		return (0);
	pt->total_philos = ft_atol(argv[1]);
	pt->lims.t_die = ft_atol(argv[2]) * 1000;
	pt->lims.t_eat = ft_atol(argv[3]) * 1000;
	pt->lims.t_slp = ft_atol(argv[4]) * 1000;
	pt->lims.max_meals = 0;
	if (argc == 6)
	{
		if (!ft_is_only_digits(argv[5]))
			return (0);
		pt->lims.max_meals = ft_atol(argv[5]);
	}
	return (pt->total_philos > 0 && pt->lims.t_die >= 0 && pt->lims.t_eat >= 0
		&& pt->lims.t_slp >= 0 && pt->lims.max_meals >= 0);
}
