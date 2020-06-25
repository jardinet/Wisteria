/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:53:51 by niboute           #+#    #+#             */
/*   Updated: 2019/06/17 11:18:23 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		ft_bzero(void *s, size_t n)
{
	char	*ptr;
	long	*lptr;

	lptr = (long*)s;
	while (n >= sizeof(long))
	{
		*(lptr++) = 0;
		n -= sizeof(long);
	}
	ptr = (char*)lptr;
	while (n)
	{
		*(ptr++) = 0;
		n--;
	}
}
