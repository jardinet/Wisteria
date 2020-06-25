/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:35:16 by niboute           #+#    #+#             */
/*   Updated: 2020/06/06 13:19:43 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_word_count(char const *s, char c)
{
	size_t		i;
	size_t		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (words);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t		words;
	char		**tab;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!(tab[j++] = ft_strndup(s + i, ft_strclen(s + i, c))))
				return (NULL);
			i += ft_strclen(s + i, c);
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
