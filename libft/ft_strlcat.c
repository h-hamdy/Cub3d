/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:28:10 by hhamdy            #+#    #+#             */
/*   Updated: 2021/11/20 15:36:41 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*s;
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	res;

	s = (char *)src;
	len_src = 0;
	i = 0;
	len_src = ft_strlen(s);
	if (!dst && size == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (size > len_dst)
		res = len_src + len_dst;
	else
		res = len_src + size;
	while (s[i] && len_dst + 1 < size)
	{
		dst[len_dst] = s[i++];
		len_dst++;
	}
	dst[len_dst] = '\0';
	return (res);
}
