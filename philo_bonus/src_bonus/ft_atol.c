/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 02:32:53 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/01 21:08:29 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h" 

static int	ft_isspace(int c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

static int	ft_issign(int c)
{
	return (c == '+' || c == '-');
}

int	ft_isdigit(int c)
{
	return ('0' <= c || c <= '9');
}

ssize_t	ft_atol(const char *str)
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
