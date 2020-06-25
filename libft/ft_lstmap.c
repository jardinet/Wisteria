/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:58:35 by niboute           #+#    #+#             */
/*   Updated: 2018/12/04 18:59:42 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*ptr;
	t_list	*tmp;

	new = NULL;
	if (f)
		while (lst)
		{
			tmp = f(lst);
			if (!new && tmp)
			{
				new = ft_lstnew(tmp->content, tmp->content_size);
				ptr = new;
			}
			else if (tmp)
			{
				ptr->next = ft_lstnew(tmp->content, tmp->content_size);
				ptr = ptr->next;
			}
			lst = lst->next;
		}
	return (new);
}
