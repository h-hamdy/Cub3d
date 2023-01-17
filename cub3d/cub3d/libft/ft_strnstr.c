/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:11:18 by hhamdy            #+#    #+#             */
/*   Updated: 2021/11/20 03:00:33 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *stack, const char *needle, size_t len)
{
	size_t	i;
	char	*s;
	char	*n;

	s = (char *)stack;
	n = (char *)needle;
	i = 0;
	if (!s)
		return (NULL);
	if (n[0] == '\0')
		return ((char *)stack);
	while (s[i] && i < len)
	{
		if (s[i] == n[0])
		{
			if (!ft_strncmp(&s[i], n, ft_strlen(n))
				&& ft_strlen(n) + i <= len)
				return (&s[i]);
		}
		i++;
	}
	return (0);
}
