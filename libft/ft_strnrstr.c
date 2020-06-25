/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 11:22:45 by niboute           #+#    #+#             */
/*   Updated: 2019/06/04 11:48:22 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strnrstr(const char *str, const char *substr, size_t len)
{
	size_t	i;
	int		j;
	size_t	slen;
	int		sublen;

	if (!*substr)
		return ((char*)str);
	i = 1;
	slen = ft_strlen(str);
	sublen = ft_strlen(substr);
	if (!slen || !sublen)
		return (NULL);
	while (i <= len && i <= slen)
	{
		j = 0;
		while (i + j <= len && i + j <= slen && (j + 1) <= sublen
				&& str[slen - (i + j)] == substr[sublen - (j + 1)])
		{
			if (sublen - (j + 1) <= 0)
				return ((char*)(str + slen - (i + j)));
			j++;
		}
		i++;
	}
	return (NULL);
}
