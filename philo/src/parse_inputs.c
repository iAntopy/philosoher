/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:48:15 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/16 18:28:17 by iamongeo         ###   ########.fr       */
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
	ft_eprintf("parse 1\n");
	if (argc < 5)
		return (-1);
	ft_eprintf("parse 2\n");
	if ((argc < 5) || (argc > 6) || !ft_is_only_digits(argv[1])
		|| !ft_is_only_digits(argv[2]) || !ft_is_only_digits(argv[3])
		|| !ft_is_only_digits(argv[4]))
		return (-1);
	ft_eprintf("parse 3\n");
	pt->np = ft_atol(argv[1]);
	pt->t_die = ft_atol(argv[2]) * 1000;
	pt->t_eat = ft_atol(argv[3]) * 1000;
	pt->t_slp = ft_atol(argv[4]) * 1000;
	pt->max_meals = 0;
	ft_eprintf("parse 4\n");
	if (argc == 6)
	{
		if (!ft_is_only_digits(argv[5]))
			return (-1);
		pt->max_meals = ft_atol(argv[5]);
	}
	ft_eprintf("parse 5\n");
	return (pt->np > 0 && pt->t_die >= 0 && pt->t_eat >= 0
		&& pt->t_slp >= 0 && pt->max_meals > 0);
}
