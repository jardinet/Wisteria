/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:42:53 by niboute           #+#    #+#             */
/*   Updated: 2018/12/04 17:24:50 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	t;
	int		i;

	t = (char)c;
	i = ft_strlen(s);
	if (!c)
		return ((char*)(s + i));
	while (i > 0)
	{
		i--;
		if (s[i] == t)
			return ((char*)(s + i));
	}
	return (NULL);
}
