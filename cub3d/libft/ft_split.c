/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:11:49 by hhamdy            #+#    #+#             */
/*   Updated: 2022/08/22 11:14:30 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{	
		if (s[i] && s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	**ft_get_word(char **str, char const *s, char c)
{
	int	i;
	int	len_word;
	int	k;

	i = 0;
	k = 0;
	len_word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		while (s[i] != c && s[i] && s[i++])
			len_word++;
		str[k] = (char *)malloc(sizeof (char) * (len_word + 1));
		k++;
		len_word = 0;
	}
	str[k] = NULL;
	return (str);
}

static char	**ft_fill_str(char **str, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[k])
	{
		j = 0;
		while (s[k] && s[k] == c)
			k++;
		if (!s[k])
			break ;
		while (s[k] && s[k] != c)
		{
			str[i][j] = s[k];
			k++;
			j++;
		}
		str[i][j] = '\0';
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**str;

	if (!s)
		return (0);
	i = 0;
	count = ft_count_word(s, c);
	str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	str = ft_get_word(str, s, c);
	str[count] = 0;
	return (ft_fill_str(str, s, c));
}
