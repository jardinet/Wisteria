/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:49:37 by niboute           #+#    #+#             */
/*   Updated: 2018/12/20 12:47:38 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_recursive_power(int n, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (n * ft_recursive_power(n, pow - 1));
}

char		*ft_itoa(int n)
{
	char	*str;
	int		pow;
	int		i;
	long	nb;
	int		neg;

	pow = 0;
	neg = n < 0 ? 1 : 0;
	nb = n < 0 ? (long)n * -1 : n;
	while (nb / ft_recursive_power(10, pow) >= 10)
		pow++;
	if (!(str = (char*)malloc(pow + 2 + neg)))
		return (NULL);
	if (neg)
		str[0] = '-';
	i = pow + neg;
	str[pow + 1 + neg] = '\0';
	while (i >= neg)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
