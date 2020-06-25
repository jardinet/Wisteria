/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:31:46 by niboute           #+#    #+#             */
/*   Updated: 2018/12/20 13:42:32 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*strnew;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	start = i;
	i = ft_strlen(s);
	i = i ? i - 1 : i;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && i >= start)
		i--;
	end = i + 1;
	if (!(strnew = (char*)malloc(end - start + 1)))
		return (NULL);
	i = start;
	start = 0;
	while (i < end)
		strnew[start++] = s[i++];
	strnew[start] = '\0';
	return (strnew);
}
