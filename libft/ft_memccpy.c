/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:45:55 by niboute           #+#    #+#             */
/*   Updated: 2018/12/20 12:49:12 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void					*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*psrc;
	unsigned char		*pdst;
	unsigned char		uc;

	uc = (unsigned char)c;
	psrc = (const unsigned char*)src;
	pdst = (unsigned char*)dst;
	while (n)
	{
		*pdst = *psrc;
		if (*pdst == uc)
			return (pdst + 1);
		pdst++;
		psrc++;
		n--;
	}
	return (NULL);
}
