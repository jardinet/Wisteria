/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:40:12 by niboute           #+#    #+#             */
/*   Updated: 2020/06/24 15:20:03 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int					get_move_wallx(t_raydata *ray)
{
	double			dist;

	if (ray->side & 3)
		dist = (ray->posx - ray->x + ((1 - ray->stepx) / 2)) / ray->dirx;
	else
		dist = (ray->posy - ray->y + ((1 - ray->stepy) / 2)) / ray->diry;
	ray->wallx = ray->side & 3 ? (dist * ray->diry) + ray->y
		: (dist * ray->dirx) + ray->x;
	ray->wallx = ray->wallx - floor(ray->wallx);
	return (ray->side);
}

int					dda_get_side(t_raydata *ray, t_map *map)
{
	t_block			*block;
	int				i;

	i = -1;
	while (++i < 2)
	{
		dda_ray_step(ray);
		if (is_out_of_bounds(ray, map))
			return (0);
		block = &map->map[(int)ray->posy][(int)ray->posx];
		if (block->isredirect & ray->side)
			return (get_move_wallx(ray));
		else if (block->iswall & ray->side)
			return (0);
	}
	return (0);
}

int					move_get_side(t_cam *eye, double *move, t_map *map,
					t_raydata *ray)
{
	ray->dirx = move[1] * (1 / MOVESPEED);
	ray->diry = move[0] * (1 / MOVESPEED);
	ray->x = eye->x;
	ray->y = eye->y;
	ray->dist = 0;
	ray->count = 0;
	setup_calculations(ray);
	return (dda_get_side(ray, map));
}

int					redirect_player_p2(t_wolf *data, t_raydata *ray,
					t_cam *eye, t_block *block)
{
	float			angle;
	unsigned char	next_side;

	next_side = ((ray->side & 3) && (block->rot == 0 || block->rot == 2)) ||
	(!(ray->side & 3) && (block->rot & 1)) ? 0 : 1;
	angle = (double)((((double)ft_modulo((int)eye->angle
		+ 90 * (int)block->rot, 360)) * M_PI) / (double)180);
	ray->dirx = cos(angle) * data->eye.sdirx - sin(angle) * data->eye.sdiry;
	ray->diry = sin(angle) * data->eye.sdirx + cos(angle) * data->eye.sdiry;
	if (next_side == 0 && ray->dirx * data->events.dir < 0)
		ray->x += -0.0001;
	else if (next_side == 1 && ray->diry * data->events.dir < 0)
		ray->y += -0.0001;
	if (ray->y < 1 || ray->y >= data->map.hei - 1
		|| ray->x < 1 || ray->x >= data->map.hei - 1
		|| data->map.map[(int)ray->y][(int)ray->x].iswall == 15)
		return (0);
	eye->angle = ft_modulo((int)eye->angle
		+ 90 * (int)block->rot, 360);
	eye->y = ray->y;
	eye->x = ray->x;
	rotate_cam(eye, &data->plane);
	return (1);
}

int					redirect_player(t_wolf *data, t_raydata *ray,
					t_block *block, double *move)
{
	ray->x = data->eye.x;
	ray->y = data->eye.y;
	if (ray->side & 3)
		ray->x += move[1];
	else
		ray->y += move[0];
	ray->x = (ray->side & 3
		? (int)ray->x : floor(ray->x)) + block->nextx;
	ray->y = (!(ray->side & 3)
		? (int)ray->y : floor(ray->y)) + block->nexty;
	redirect_ray_horizontal(ray, block);
	return (redirect_player_p2(data, ray, &data->eye, block));
}
