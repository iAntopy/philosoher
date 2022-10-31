/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:32:36 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/27 23:55:45 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
