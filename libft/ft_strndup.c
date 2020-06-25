/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:43:06 by niboute           #+#    #+#             */
/*   Updated: 2018/12/20 13:40:46 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strndup(const char *str, size_t size)
{
	char	*dup;

	if (!(dup = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_strncpy(dup, str, size);
	dup[size] = '\0';
	return (dup);
}
