/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:51:29 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/31 03:35:37 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
/*
int	main(int argc, char **argv)
{
	char	n1[20];
	char	n2[20];

	if (argc < 3)
		return (1);
	ft_putnbr_buff(n1, ft_atol(argv[1]));
	ft_putnbr_buff(n2, ft_atol(argv[2]));
	printf("n1: %s, n2: %s\n", n1, n2);
	return (0);
}
*/
