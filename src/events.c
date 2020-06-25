/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:37:47 by niboute           #+#    #+#             */
/*   Updated: 2020/06/24 15:33:46 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void				keyboard_events(t_wolf *data)
{
	const Uint8		*state;

	state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
		wipeout(data, EXIT_SUCCESS);
	data->events.dir = state[SDL_SCANCODE_UP] - state[SDL_SCANCODE_DOWN];
	data->events.rot_dir = state[SDL_SCANCODE_LEFT] - state[SDL_SCANCODE_RIGHT];
	if (data->events.dir)
		move(&data->eye, data->map.map, data);
	if (data->events.rot_dir)
	{
		data->eye.angle = ft_modulo(data->eye.angle - data->events.rot_dir * 2,
			360);
		rotate_cam(&data->eye, &data->plane);
	}
}

void				handle_events(SDL_Event *event, t_wolf *data)
{
	if (event->type == SDL_QUIT)
		wipeout(data, EXIT_SUCCESS);
}

void				setup_move(double *move, unsigned char *side, t_cam *eye,
						t_block **map)
{
	if ((int)(move[1] + eye->x) != (int)eye->x &&
		(map[(int)eye->y][(int)(move[1] + eye->x)].iswall & side[1])
		&& !(map[(int)eye->y][(int)(move[1] + eye->x)].isredirect & side[1]))
		move[1] = 0;
	if ((int)(move[0] + eye->y) != (int)eye->y &&
		(map[(int)(move[0] + eye->y)][(int)eye->x].iswall & side[0])
		&& !(map[(int)(move[0] + eye->y)][(int)eye->x].isredirect & side[0]))
		move[0] = 0;
}

int					move(t_cam *eye, t_block **map, t_wolf *data)
{
	unsigned char	side[2];
	t_block			*block;
	double			move[2];
	t_raydata		ray;

	ray.side = 0;
	move[1] = data->eye.dirx * MOVESPEED * data->events.dir;
	move[0] = data->eye.diry * MOVESPEED * data->events.dir;
	side[0] = (data->eye.diry * data->events.dir) > 0 ? 4 : 8;
	side[1] = (data->eye.dirx * data->events.dir) > 0 ? 1 : 2;
	setup_move(&move[0], &side[0], eye, map);
	block = &map[(int)(eye->y + move[0])][(int)(eye->x + move[1])];
	move_get_side(eye, &move[0], &data->map, &ray);
	if (block->isredirect & ray.side)
		return (redirect_player(data, &ray, block, &move[0]));
	if (!(map[(int)(move[0] + eye->y)][(int)(move[1] + eye->x)].iswall
		& ray.side) || ((int)(move[1] + eye->x) == (int)eye->x)
		|| ((int)(move[0] + eye->y) == (int)eye->y))
	{
		eye->y += move[0];
		eye->x += move[1];
	}
	return (0);
}
