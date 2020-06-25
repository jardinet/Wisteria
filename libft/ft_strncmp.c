/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:14:49 by niboute           #+#    #+#             */
/*   Updated: 2018/12/20 13:40:18 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && (unsigned char)*s1 == (unsigned char)*s2 && n)
	{
		s1++;
		s2++;
		n--;
	}
	return (n ? (unsigned char)*s1 - (unsigned char)*s2 : 0);
}
