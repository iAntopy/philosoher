/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:42:42 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/01 21:46:46 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// clears mem to zero at dest for size bytes.
void	ft_memclear(void *dest, size_t size)
{
	size_t			*p;
	unsigned char	*c;

	if (!dest || !size)
		return ;
	p = (size_t *)dest;
	c = (unsigned char *)dest;
	while (size >= sizeof(size_t))
	{
		*(p++) = 0;
		size -= sizeof(size_t);
	}
	c = (unsigned char *)p;
	while (size)
	{
		*(c++) = 0;
		size -= sizeof(unsigned char);
	}
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
