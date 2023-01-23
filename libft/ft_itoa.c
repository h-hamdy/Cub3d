/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:02:57 by hhamdy            #+#    #+#             */
/*   Updated: 2021/11/17 20:15:30 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_fill_nbr(long num, char *nbr, int len_n)
{
	int	sign;

	sign = 0;
	if (num < 0)
	{
		num *= -1;
		sign = 1;
	}
	while (len_n > 0)
	{
		nbr[len_n - 1] = (num % 10) + '0';
		len_n--;
		num /= 10;
	}
	if (sign)
		nbr[0] = '-';
	return (nbr);
}

char	*ft_itoa(int n)
{
	int		len_n;
	char	*nbr;
	long	num;

	len_n = ft_len(n);
	num = n;
	nbr = (char *)malloc(sizeof (char) * (len_n + 1));
	if (!nbr)
		return (NULL);
	nbr[len_n] = '\0';
	nbr = ft_fill_nbr(num, nbr, len_n);
	return (nbr);
}
