/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:41:50 by niboute           #+#    #+#             */
/*   Updated: 2018/12/20 12:48:36 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *lstnew;

	if (!(lstnew = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		if (!(lstnew->content = ft_memalloc(content_size)))
		{
			free(lstnew);
			return (NULL);
		}
		ft_memcpy(lstnew->content, content, content_size);
	}
	else
		lstnew->content = NULL;
	lstnew->content_size = !content ? 0 : content_size;
	lstnew->next = NULL;
	return (lstnew);
}
