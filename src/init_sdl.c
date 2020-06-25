/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:17:48 by niboute           #+#    #+#             */
/*   Updated: 2020/06/16 14:01:35 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		create_window(t_sdl_data *win)
{
	if (!(win->win = SDL_CreateWindow(win->desc, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINWID, WINHEI, SDL_WINDOW_SHOWN)))
		return (0);
	if (!(win->renderer = SDL_CreateRenderer(win->win, -1,
		SDL_RENDERER_ACCELERATED)))
		return (0);
	if (!(win->maintext = SDL_CreateTexture(win->renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		WINWID, WINHEI)))
		return (0);
	win->mainrect.x = 0;
	win->mainrect.y = 0;
	win->mainrect.w = WINWID;
	win->mainrect.h = WINHEI;
	return (1);
}

int		init_sdl(t_sdl_data *win)
{
	if (!(win->desc = ft_strdup("Wolf3d")))
		return (0);
	if (SDL_Init(SDL_INIT_VIDEO))
		return (0);
	if (!(create_window(win)))
		return (0);
	return (1);
}
