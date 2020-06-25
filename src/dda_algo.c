/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:13:17 by niboute           #+#    #+#             */
/*   Updated: 2020/06/16 16:24:54 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void			setup_calculations(t_raydata *ray)
{
	ray->wallx = 0;
	ray->posx = (int)ray->x;
	ray->posy = (int)ray->y;
	ray->deltax = fabs(1 / ray->dirx);
	ray->deltay = fabs(1 / ray->diry);
	ray->stepx = ray->dirx > 0 ? 1 : -1;
	ray->stepy = ray->diry > 0 ? 1 : -1;
	ray->block_dist_x = ray->stepx > 0
		? (ray->posx - ray->x + 1) * ray->deltax
		: (ray->x - ray->posx) * ray->deltax;
	ray->block_dist_y = ray->stepy > 0
		? (ray->posy - ray->y + 1) * ray->deltay
		: (ray->y - ray->posy) * ray->deltay;
}

void			wall_hit(t_wolf *data, t_raydata *ray, t_block *block)
{
	double		dist;

	if (ray->count > MAX_RAY_DIST || ray->redir_count > MAX_REDIRECTS)
		return ;
	if (ray->side & 3)
		dist = (ray->posx - ray->x + ((1 - ray->stepx) / 2)) / ray->dirx;
	else
		dist = (ray->posy - ray->y + ((1 - ray->stepy) / 2)) / ray->diry;
	ray->dist += dist;
	ray->wallx = ray->side & 3 ? (dist * ray->diry) + ray->y
		: (dist * ray->dirx) + ray->x;
	ray->wallx = ray->wallx - floor(ray->wallx);
	if (isnan(ray->dist) || isnan(ray->wallx))
		return ;
	if (block->isredirect & ray->side)
	{
		redirect_ray(ray, block);
		setup_calculations(ray);
		dda_alg(data, ray);
	}
	else if (ray->count == 1000 || block->iswall & ray->side)
		draw_line(data, ray, block);
}

int				is_out_of_bounds(t_raydata *ray, t_map *map)
{
	if (ray->posx < 0 || ray->posx >= map->wid
		|| ray->posy < 0 || ray->posy >= map->hei)
		return (1);
	return (0);
}

void			dda_ray_step(t_raydata *ray)
{
	if (ray->block_dist_x < ray->block_dist_y)
	{
		ray->side = ray->stepx == 1 ? 1 : 2;
		ray->block_dist_x += ray->deltax;
		ray->posx += ray->stepx;
	}
	else
	{
		ray->side = ray->stepy == 1 ? 4 : 8;
		ray->block_dist_y += ray->deltay;
		ray->posy += ray->stepy;
	}
}

void			dda_alg(t_wolf *data, t_raydata *ray)
{
	t_block		*ptr;

	while (1)
	{
		ray->count++;
		dda_ray_step(ray);
		if (is_out_of_bounds(ray, &data->map))
			return ;
		ptr = &data->map.map[(int)ray->posy][(int)ray->posx];
		if (ray->count >= 1000
			|| ptr->iswall & ray->side || ptr->isredirect & ray->side)
		{
			wall_hit(data, ray, &(data->map.map[ray->posy][ray->posx]));
			return ;
		}
	}
}
