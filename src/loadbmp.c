/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadbmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:11:00 by nboute            #+#    #+#             */
/*   Updated: 2020/06/20 17:06:07 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	*check_data(t_bmp_if *inf, t_texture *text)
{
	if (inf->height <= 0 || inf->width <= 0 || inf->bits != 24)
		return (NULL);
	text->height = inf->height;
	text->width = inf->width;
	return (text);
}

void	*read_check_data(int fd, t_bmp_hd *head, t_bmp_if *inf,
						t_texture *text)
{
	int		ret;
	char	buff[41];

	if ((ret = read(fd, buff, 14)) != 14)
		return (NULL);
	head->type = *(unsigned short*)buff;
	head->size = *(unsigned int*)(buff + 2);
	head->res1 = *(unsigned short*)(buff + 6);
	head->res2 = *(unsigned short*)(buff + 8);
	if ((ret = read(fd, buff, 40)) != 40)
		return (NULL);
	inf->size = *(unsigned int*)(buff);
	inf->width = *(int*)(buff + 4);
	inf->height = *(int*)(buff + 8);
	inf->planes = *(unsigned short*)(buff + 12);
	inf->bits = *(unsigned short*)(buff + 14);
	inf->compression = *(unsigned int*)(buff + 16);
	inf->imgsize = *(unsigned int*)(buff + 20);
	inf->xres = *(int*)(buff + 24);
	inf->yres = *(int*)(buff + 28);
	inf->nbcols = *(unsigned int*)(buff + 32);
	inf->impcols = *(unsigned int*)(buff + 36);
	return (check_data(inf, text));
}

void	*destroy_texture_str(int **texture, char *str,
							t_bmp_if *inf)
{
	int	y;

	y = 0;
	while (y < inf->height)
		free(texture[y++]);
	free(str);
	return (NULL);
}

int		**get_texture_p2(int fd, int **texture, t_bmp_if *inf,
						char *buff)
{
	unsigned int	i;
	int				x;
	int				y;
	int				ret;

	i = 0;
	y = inf->height;
	while (--y >= 0 && i < inf->imgsize)
	{
		x = -1;
		if ((ret = read(fd, buff, (inf->bits * inf->width) / 8)) <= 0)
			return (destroy_texture_str(texture, buff, inf));
		buff[ret] = '\0';
		while (++x < inf->width)
			texture[y][x] = (buff[x * 3] + (buff[x * 3 + 1] << 8) +
					(buff[x * 3 + 2] << 16)) & 0x00FFFFFF;
		i += inf->width * 3;
	}
	ft_strdel(&buff);
	return (texture);
}

int		**get_texture(int fd, int **texture, t_bmp_if *inf)
{
	char			*buff;
	unsigned int	i;
	int				y;

	i = 14 + 40 + 4 * inf->nbcols;
	y = 0;
	while (y < inf->height)
		if (!(texture[y++] = (int*)ft_calloc(sizeof(int), inf->width)))
		{
			y--;
			while (--y >= 0)
				free(texture[y]);
			return (NULL);
		}
	y = inf->height;
	if (!(buff = (char*)ft_calloc((inf->bits / 8), (inf->width) + 1)))
	{
		while (--y >= 0)
			free(texture[y]);
		return (NULL);
	}
	return (get_texture_p2(fd, texture, inf, buff));
}
