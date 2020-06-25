/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:22:21 by niboute           #+#    #+#             */
/*   Updated: 2019/06/27 14:25:23 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		*ft_memdup(void *ptr, size_t size)
{
	void	*dup;

	if (!(dup = malloc(size)))
		return (NULL);
	return (ft_memcpy(dup, ptr, size));
}
