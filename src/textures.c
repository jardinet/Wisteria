/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 17:27:32 by mwragg            #+#    #+#             */
/*   Updated: 2020/06/24 16:36:33 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

t_texture	*bmp_to_texture_p2(t_bmp_if *inf, int fd,
								t_texture *texture)
{
	if (!(texture->text = (int**)ft_calloc(sizeof(int*), inf->height)))
	{
		close(fd);
		free(texture);
		return (NULL);
	}
	if (!(get_texture(fd, texture->text, inf)))
	{
		close(fd);
		free(texture->text);
		free(texture);
		return (NULL);
	}
	close(fd);
	return (texture);
}

t_texture	*bmp_to_texture(char *name)
{
	int			fd;
	char		*buff;
	t_bmp_hd	head;
	t_bmp_if	inf;
	t_texture	*texture;

	if ((fd = open(name, O_RDONLY)) < 0)
		return (NULL);
	if (!(texture = (t_texture*)ft_calloc(sizeof(t_texture), 1)))
	{
		close(fd);
		return (NULL);
	}
	if (!read_check_data(fd, &head, &inf, texture)
			|| !(buff = ft_calloc(sizeof(char), (4 * inf.nbcols + 1))))
	{
		close(fd);
		free(texture);
		return (NULL);
	}
	if (inf.nbcols)
		read(fd, buff, 4 * inf.nbcols);
	ft_strdel(&buff);
	return (bmp_to_texture_p2(&inf, fd, texture));
}

int			get_paths_text(int fd, t_texlist *text)
{
	int		i;
	char	*line;
	int		tmp;

	i = 0;
	tmp = text->nb_text;
	if ((text->textures = (t_texture **)ft_calloc(sizeof(t_texture *),
					text->nb_text)) == NULL)
		return (ft_error("Error : malloc(3) was unable to allocate memory."));
	while (tmp && (get_next_line(fd, &line, 0) > 0))
	{
		if ((text->textures[i] = bmp_to_texture(line)) == NULL)
			return (ft_errordel("Error : Expected texture could not be read.",
		&line));
			if (text->textures[i]->width != TEXTURE_SIZE
			|| text->textures[i]->height != TEXTURE_SIZE)
			return (ft_errordel("Error: Invalid texture format.", &line));
		ft_strdel(&line);
		tmp--;
		i++;
	}
	if (tmp != 0)
		return (ft_error("Error : Number of paths and textures do not match."));
	return (1);
}

int			get_textures(int fd, t_texlist *text)
{
	int		i;
	char	*line;

	i = 0;
	if (get_next_line(fd, &line, 0) < 1)
		return (0);
	text->nb_text = ft_atoi(line);
	if (text->nb_text <= 0 || text->nb_text > NB_TEXT_MAX)
	{
		ft_strdel(&line);
		return (0);
	}
	while (ft_isdigit(line[i]) && i < 3)
		i++;
	if (line[i] != '\0')
		return (0);
	ft_strdel(&line);
	if (!get_paths_text(fd, text))
		return (0);
	return (text->nb_text);
}
