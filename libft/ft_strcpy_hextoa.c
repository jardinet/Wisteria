/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_hextoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:11:26 by niboute           #+#    #+#             */
/*   Updated: 2019/10/16 17:11:48 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcpy_hextoa(char *dest, unsigned int hex, int maj)
{
	int		i;

	dest[0] = '0';
	dest[1] = !maj ? 'x' : 'X';
	i = 9;
	while (i > 1)
	{
		if (!maj)
			dest[i] = (hex & 15) >= 10
			? (hex & 15) - 10 + 'a' : (hex & 15) + '0';
		else
			dest[i] = (hex & 15) >= 10
			? (hex & 15) - 10 + 'A' : (hex & 15) + '0';
		i--;
		hex >>= 4;
	}
	dest[10] = '\0';
	return (dest);
}
