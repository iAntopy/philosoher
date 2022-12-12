/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:42:42 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/10 20:38:35 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	timer_us(t_tv *t0)
{
	t_tv	curr_t;
	ssize_t	delta_t;

	if (!t0)
	{
		ft_eprintf("timer_ms : missing input args pt or t0 ptrs.\n");
		return (0);
	}
	gettimeofday(&curr_t, NULL);
	delta_t = (ssize_t)(curr_t.tv_sec - t0->tv_sec) * 1000000;
	delta_t += (ssize_t)(curr_t.tv_usec - t0->tv_usec);
	return (delta_t);
}

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_memclear(void *dest, size_t size)
{
	size_t	*d;
	char	*c;
	size_t	div;
	size_t	mod;

	d = (size_t *)dest;
	div = size / sizeof(size_t);
	mod = size % sizeof(size_t);
	while (div--)
		*(d++) = 0;
	c = (char *)d;
	while (mod--)
		*(c++) = '\0';
}

static char	*rec_putnbr(char *buff, size_t n)
{
	if (n > 9)
		buff = rec_putnbr(buff, n / 10);
	*buff = '0' + (n % 10);
	return (buff + 1);
}

int	ft_putnbr_buff(char *buff, ssize_t n)
{
	char	*b;

	b = buff;
	*b = '-';
	b = rec_putnbr(b + (n < 0), n * (1 - (2 * (n < 0))));
	*(b++) = ' ';
	*b = '\0';
	return (b - buff);
}
