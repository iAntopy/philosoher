/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:16:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/01 21:09:16 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	malloc_free_p(size_t size, void **ptr)
{	
	if (size)
	{
		if (!ptr)
			return (0);
		*ptr = malloc(size);
		return (*ptr != NULL);
	}
	else if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (1);
}

int	ft_malloc_p(size_t size, void **ptr)
{
	void	*p;

	if (!ptr || !size)
		return (0);
	p = NULL;
	if (*ptr)
	{
		ft_eprintf("WARNING : ft_malloc_p should only malloc if *ptr is NULL.");
		ft_eprintf(" Clear ptr before calling ft_malloc_p\n");
	}
	p = malloc(size);
	*ptr = p;
	return (p != NULL);
}

int	ft_calloc_p(size_t size, void **ptr)
{
	void	*p;

	p = NULL;
	if (!ft_malloc_p(size, &p))
		return (0);
	ft_memclear(p, size);
	*ptr = p;
	return (1);
}

int	ft_free_p(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (1);
}
