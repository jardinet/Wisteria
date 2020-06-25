/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:24:45 by niboute           #+#    #+#             */
/*   Updated: 2018/12/20 12:49:26 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void					*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		uc;
	const unsigned char	*str;

	uc = (unsigned char)c;
	str = (const unsigned char*)s;
	while (n)
	{
		if (*str == uc)
			return ((void*)str);
		str++;
		n--;
	}
	return (NULL);
}
