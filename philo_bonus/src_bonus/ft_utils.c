/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:42:42 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/14 22:17:34 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

ssize_t	timer_us(t_tv *t0, pthread_mutex_t *lock)
{
	t_tv	curr_t;
	ssize_t	delta_t;

	if (!t0)
	{
		ft_eprintf("timer_us : missing input argst0 ptr.\n");
		return (0);
	}
	gettimeofday(&curr_t, NULL);

	ft_eprintf("timer_us : trying to lock\n");
	pthread_mutex_lock(lock);
	ft_eprintf("timer_us : lock acquired\n");
	delta_t = (ssize_t)(curr_t.tv_sec - t0->tv_sec) * 1000000;
	delta_t += (ssize_t)(curr_t.tv_usec - t0->tv_usec);
	ft_eprintf("timer_us : trying to unlock\n");
	pthread_mutex_unlock(lock);
	ft_eprintf("timer_us : unlock SUCCESSFULL\n");
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


