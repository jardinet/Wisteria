/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 21:05:55 by marvin            #+#    #+#             */
/*   Updated: 2020/06/23 21:39:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		destroy_gnl_files(t_file **files)
{
	if (!files)
		return (0);
	while (*files)
		create_destroy_file(0, (*files)->fd, files);
	return (0);
}
