/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:39:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/29 01:05:53 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

static int	ft_isspace(int c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

static int	ft_issign(int c)
{
	return (c == '+' || c == '-');
}

int	ft_atoi(const char *str)
{
	size_t	nb;
	int		sign;

	nb = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && ft_issign(*str))
	{
		if (!ft_isdigit(*(str + 1)))
			return (0);
		sign -= 2 * (*str == '-');
		str++;
	}
	while (*str && ft_isdigit(*str))
		nb = (nb * 10) + (*(str++) - '0');
	return (sign * nb);
}
