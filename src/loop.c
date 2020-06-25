/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:04:50 by niboute           #+#    #+#             */
/*   Updated: 2020/06/24 17:11:37 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void			*raycast(void *ptr)
{
	t_thread	*thread_data;
	int			i;
	t_raydata	*ray;
	t_wolf		*data;

	thread_data = (t_thread*)ptr;
	ray = &thread_data->ray;
	data = thread_data->data;
	i = -1;
	while (++i < WINWID / CPU_THREADS)
	{
		ray->screenx = i + thread_data->x;
		ray->dirx = ft_dmap(ray->screenx, WINWID, -1, 1) * data->plane.dirx
			+ data->eye.dirx;
		ray->diry = ft_dmap(ray->screenx, WINWID, -1, 1) * data->plane.diry
			+ data->eye.diry;
		ray->x = data->eye.x;
		ray->y = data->eye.y;
		ray->dist = 0;
		ray->count = 0;
		ray->redir_count = 0;
		setup_calculations(ray);
		dda_alg(data, ray);
	}
	return (NULL);
}

void			raycast_threads(t_thread *threads)
{
	int			i;

	i = 0;
	while (i < CPU_THREADS)
	{
		pthread_create(&threads[i].thread, NULL, raycast, &threads[i]);
		i++;
	}
	i = 0;
	while (i < CPU_THREADS)
	{
		pthread_join(threads[i].thread, NULL);
		i++;
	}
}

void			init_threads(t_thread *threads, t_wolf *data)
{
	int	i;

	i = 0;
	while (i < CPU_THREADS)
	{
		threads[i].x = (i * WINWID) / CPU_THREADS;
		threads[i].data = data;
		i++;
	}
}

void			loop(t_wolf *data)
{
	t_thread	threads[CPU_THREADS];
	int			i;
	SDL_Event	event;

	init_threads((t_thread*)&threads[0], data);
	while (1)
	{
		while (SDL_PollEvent(&event))
			handle_events(&event, data);
		keyboard_events(data);
		SDL_LockTexture(data->win.maintext, NULL, (void*)&data->win.img, &i);
		copy_floor_roof(&data->win);
		raycast_threads((t_thread*)&threads[0]);
		SDL_UnlockTexture(data->win.maintext);
		SDL_RenderCopy(data->win.renderer, data->win.maintext, NULL, NULL);
		SDL_RenderPresent(data->win.renderer);
	}
}
