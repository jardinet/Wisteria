/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:16:12 by niboute           #+#    #+#             */
/*   Updated: 2018/12/20 12:54:52 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strdup(const char *str)
{
	char	*dup;
	size_t	n;

	n = ft_strlen(str);
	if (!(dup = (char*)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	return (ft_strcpy(dup, str));
}
