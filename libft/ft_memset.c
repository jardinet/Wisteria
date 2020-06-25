/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:42:46 by niboute           #+#    #+#             */
/*   Updated: 2019/08/06 16:05:22 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	uc;
	unsigned long	ul;
	unsigned long	*lptr;

	lptr = (unsigned long*)b;
	uc = (unsigned char)c;
	ul = uc;
	ul = (ul << 56) + (ul << 48) + (ul << 40) + (ul << 32) + (ul << 24)
		+ (ul << 16) + (ul << 8) + ul;
	while (len >= sizeof(long))
	{
		*(lptr++) = ul;
		len -= sizeof(long);
	}
	ptr = (unsigned char*)lptr;
	while (len)
	{
		*(ptr++) = uc;
		len--;
	}
	return (b);
}
