/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:43:58 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/17 01:23:55 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define L_MAX 9223372036854775807

unsigned long long	ft_atoi(const char *str)
{
	size_t				i;
	unsigned long long	n;
	int					mult;

	i = 0;
	mult = 1;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			mult *= -1;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		n = n * 10 + (str[i++] - '0');
		if (n > 9223372036854775807)
			return (1);
	}
	return (mult * n);
}
