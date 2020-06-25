/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wipeout.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 19:25:55 by mwragg            #+#    #+#             */
/*   Updated: 2020/06/24 15:34:45 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	free_textures(t_texlist *text)
{
	int	i;
	int	j;

	i = 0;
	if (!(text->textures))
		return ;
	while (i < text->nb_text && text->textures[i])
	{
		j = 0;
		if (text->textures[i]->text)
		{
			while (j < text->textures[i]->height && text->textures[i]->text[j])
			{
				ft_memdel((void**)&(text->textures[i]->text[j]));
				j++;
			}
			ft_memdel((void**)&(text->textures[i]->text));
		}
		ft_memdel((void**)&(text->textures[i]));
		i++;
	}
	ft_memdel((void**)&(text->textures));
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!(map->map))
		return ;
	while (i < map->hei && map->map[i])
		ft_memdel((void**)&(map->map[i++]));
	ft_memdel((void**)&(map->map));
}

void	free_sdl(t_sdl_data *win)
{
	win->img = NULL;
	if (win->maintext)
		SDL_DestroyTexture(win->maintext);
	win->maintext = NULL;
	if (win->renderer)
		SDL_DestroyRenderer(win->renderer);
	win->renderer = NULL;
	if (win->win)
		SDL_DestroyWindow(win->win);
	win->win = NULL;
	ft_strdel(&win->desc);
	SDL_Quit();
}

void	wipeout(t_wolf *data, int ret)
{
	free_textures(&(data->text));
	free_map(&(data->map));
	free_sdl(&data->win);
	get_next_line(0, NULL, 1);
	exit(ret);
}
