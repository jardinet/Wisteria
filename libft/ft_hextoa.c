/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:46:15 by niboute           #+#    #+#             */
/*   Updated: 2019/06/17 12:48:35 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_hextoa(unsigned int hex, int maj)
{
	char	*str;
	int		i;

	if (!(str = (char*)malloc(sizeof(char) * 12)))
		return (NULL);
	str[0] = '0';
	str[1] = !maj ? 'x' : 'X';
	i = 10;
	while (i > 1)
	{
		if (!maj)
			str[i] = (hex & 15) >= 10 ?
				(hex & 15) - 10 + 'a' : (hex & 15) + '0';
		else
			str[i] = (hex & 15) >= 10 ?
				(hex & 15) - 10 + 'A' : (hex & 15) + '0';
		i--;
		hex >>= 4;
	}
	str[11] = '\0';
	return (str);
}
