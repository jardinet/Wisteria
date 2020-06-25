/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:56:35 by niboute           #+#    #+#             */
/*   Updated: 2019/06/17 11:42:45 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*pdst;
	const char	*psrc;

	if (!src && !dst)
		return (NULL);
	psrc = (const char*)src;
	pdst = (char*)dst;
	if ((psrc > pdst && psrc - psrc < (long)n)
			|| (pdst > psrc && pdst - psrc < (long)n))
		ft_memmove(dst, src, n);
	while (n)
	{
		*pdst++ = *psrc++;
		n--;
	}
	return (dst);
}
