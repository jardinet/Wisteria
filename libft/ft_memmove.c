/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:39:39 by niboute           #+#    #+#             */
/*   Updated: 2019/06/17 11:41:44 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*pdst;
	const char	*psrc;

	if (!dst && !src)
		return (NULL);
	pdst = (char*)dst;
	psrc = (const char*)src;
	i = (dst > src) ? len : 0;
	if (dst > src)
	{
		while (i)
		{
			i--;
			pdst[i] = psrc[i];
		}
	}
	else
		while (i < len)
		{
			pdst[i] = psrc[i];
			i++;
		}
	return (dst);
}
