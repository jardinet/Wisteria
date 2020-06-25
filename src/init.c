/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 15:12:18 by mwragg            #+#    #+#             */
/*   Updated: 2020/06/25 11:56:27 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int			init_camera(t_cam *eye, t_vector *plane)
{
	eye->dirx = 1;
	eye->diry = 0;
	eye->fov = 66;
	plane->x = eye->dirx + eye->x;
	plane->y = eye->diry + eye->y;
	plane->dirx = 0;
	plane->diry = tan(((eye->fov * M_PI) / 180) / 2);
	eye->angle = 0;
	eye->sdirx = eye->dirx;
	eye->sdiry = eye->diry;
	eye->splanex = plane->dirx;
	eye->splaney = plane->diry;
	return (0);
}
