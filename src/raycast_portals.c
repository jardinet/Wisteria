/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_portals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:24:12 by niboute           #+#    #+#             */
/*   Updated: 2020/06/24 16:36:21 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void				redirect_ray_horizontal(t_raydata *ray, t_block *block)
{
	if (ray->side & 3)
	{
		if (block->rot == 1)
			ray->x += 1.0 - ray->wallx;
		else if (block->rot == 2)
			ray->y += 1.0 - ray->wallx;
		else if (block->rot == 3)
			ray->x += ray->wallx;
		else
			ray->y += ray->wallx;
	}
	else
	{
		if (block->rot == 1)
			ray->y += ray->wallx;
		else if (block->rot == 2)
			ray->x += 1.0 - ray->wallx;
		else if (block->rot == 3)
			ray->y += 1.0 - ray->wallx;
		else
			ray->x += ray->wallx;
	}
}

void				redirect_ray(t_raydata *ray, t_block *block)
{
	double			angle;
	double			tmp;
	unsigned char	next_side;

	angle = 0;
	ray->redir_count++;
	ray->x = ray->posx + block->nextx;
	ray->y = ray->posy + block->nexty;
	redirect_ray_horizontal(ray, block);
	angle = ((double)(90 * (int)block->rot) * M_PI) / 180.0f;
	tmp = cos(angle) * ray->dirx - sin(angle) * ray->diry;
	ray->diry = sin(angle) * ray->dirx + cos(angle) * ray->diry;
	ray->dirx = tmp;
	next_side = ((ray->side & 3) && (block->rot == 0 || block->rot == 2)) ||
	(!(ray->side & 3) && (block->rot & 1)) ? 0 : 1;
	if (next_side == 0 && ray->dirx < 0)
		ray->y += -0.0001;
	else if (next_side == 1 && ray->diry < 0)
		ray->x += -0.0001;
}
