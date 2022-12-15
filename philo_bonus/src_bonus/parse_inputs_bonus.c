/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:34:18 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/14 20:17:35 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	ft_eprintf("parsing : argv, 1: %s, 2: %s, 3: %s, 4: %s\n", argv[1], argv[2], argv[3], argv[4]);
	pt->np = ft_atol(argv[1]);
	pt->t_die = ft_atol(argv[2]) * 1000;
	pt->t_eat = ft_atol(argv[3]) * 1000;
	pt->t_slp = ft_atol(argv[4]) * 1000;
	pt->max_meals = 0;
	if (argc == 6)
	{
		if (!ft_is_only_digits(argv[5]))
			return (-1);
		pt->max_meals = ft_atol(argv[5]);
	}
	return (pt->np > 0 && pt->t_die >= 0 && pt->t_eat >= 0
		&& pt->t_slp >= 0 && pt->max_meals > 0);
}
