/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 15:20:27 by mwragg            #+#    #+#             */
/*   Updated: 2020/06/24 16:31:45 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		rotate_cam(t_cam *eye, t_vector *plane)
{
	double	angle;

	angle = (double)(((double)eye->angle * M_PI) / (double)180);
	eye->dirx = cos(angle) * eye->sdirx - sin(angle) * eye->sdiry;
	eye->diry = sin(angle) * eye->sdirx + cos(angle) * eye->sdiry;
	plane->dirx = cos(angle) * eye->splanex - sin(angle)
		* eye->splaney;
	plane->diry = sin(angle) * eye->splanex + cos(angle)
		* eye->splaney;
}

void		draw_line(t_wolf *data, t_raydata *ray, t_block *block)
{
	int	tex[3];
	int	linehei;
	int	y;
	int	i;
	int	end;

	if (ray->side == 2 || ray->side == 8)
		ray->wallx = 1 - ray->wallx;
	linehei = ray->dist >= 0.10 ? (double)WINHEI / ray->dist : WINHEI * 10;
	y = linehei > WINHEI ? 0 : WINHEI / 2 - linehei / 2;
	tex[0] = ((block->texid >> (!(ray->side & 1)
		* ray->side * (4 - ray->side / 8))) & 255) - 1;
	tex[2] = (int)ft_dmap(ray->wallx, 1, 0, 63);
	i = linehei > WINHEI ? linehei / 2 - WINHEI / 2 : 0;
	end = linehei > WINHEI ? linehei / 2 + WINHEI / 2 : linehei;
	while (i < end)
	{
		tex[1] = (int)ft_dmap(i, linehei, 0, 63);
		data->win.img[y * WINWID + ray->screenx] =
			data->text.textures[tex[0]]->text[tex[1]][tex[2]];
		i++;
		y++;
	}
}

void		copy_floor_roof(t_sdl_data *win)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINHEI / 2)
	{
		j = 0;
		while (j < WINWID)
		{
			win->img[i * WINWID + j] = SKY_COLOR;
			win->img[(i + WINHEI / 2) * WINWID + j] = FLOOR_COLOR;
			j++;
		}
		i++;
	}
}
