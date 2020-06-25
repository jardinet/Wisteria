/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:51:59 by mwragg            #+#    #+#             */
/*   Updated: 2020/06/24 16:48:28 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int			get_dimensions(char *line, int *a, int *b)
{
	int	istar;
	int	i;
	int	ndigit;

	istar = ft_strichr(line, '*');
	if (istar == -1 || istar == 0 || (istar == (int)ft_strlen(line)))
		return (ft_error("Error : Please consult the dimension format."));
	i = 0;
	while (line[i])
	{
		ndigit = 0;
		while (ft_isdigit(line[i]) && ndigit < 4 && ++i)
			ndigit++;
		if (line[i] != '\0' && i != istar)
			return (ft_error("Error : Please consult the dimension format."));
		if (line[i] != '\0')
			i++;
	}
	*a = ft_atoi(line);
	*b = ft_atoi(line + istar + 1);
	if (*a < MIN_MAP || *a > MAX_MAP || *b < MIN_MAP || *b > MAX_MAP)
		return (ft_error("Error : Please give dimensions between 5 and 1000."));
	return (1);
}

int			check_player_pos(t_cam *eye, t_map *map)
{
	if (map->map[(int)eye->y][(int)eye->x].iswall != 0
	|| map->map[(int)eye->y][(int)eye->x].isredirect != 0)
		return (ft_error("Error : Player's starting position is inside "
		"a wall/portal."));
	eye->y += 0.5;
	eye->x += 0.5;
	return (1);
}

int			get_dimensions_double(char *line, double *a, double *b, t_map *map)
{
	int	istar;
	int	i;
	int	ndigit;

	istar = ft_strichr(line, SPACE);
	if (istar == -1 || istar == 0 || (istar == (int)ft_strlen(line)))
		return (ft_error("Error : Please consult the start pos. format."));
	i = 0;
	while (line[i])
	{
		ndigit = 0;
		while (ft_isdigit(line[i]) && ndigit < 4 && ++i)
			ndigit++;
		if (line[i] != '\0' && i != istar)
			return (ft_error("Error : Please consult the start pos. format."));
		if (line[i] != '\0')
			i++;
	}
	*a = (double)ft_atoi(line);
	*b = (double)ft_atoi(line + istar + 1);
	if (*a < 1 || *a > (map->hei - 2) || *b < 1 || *b > (map->wid - 2))
		return (ft_error("Error : Start position on/outside of borders."));
	return (1);
}

int			parsing(char *file, t_wolf *data)
{
	int		fd;
	char	*line;
	int		nbtext;

	line = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (ft_error("Error : Unable to open file"));
	if (get_next_line(fd, &line, 0) != 1)
		return (ft_error("Error : Please consult !usage for map format."));
	if (!get_dimensions(line, &(data->map.hei), &(data->map.wid)))
		return (ft_errordel("", &line));
	ft_strdel(&line);
	if (get_next_line(fd, &line, 0) != 1)
		return (ft_error("Error : Please consult !usage for map format."));
	if (!get_dimensions_double(line, &(data->eye.y), &(data->eye.x),
							&(data->map)))
		return (ft_errordel("", &line));
	ft_strdel(&line);
	if (!(nbtext = get_textures(fd, &(data->text))))
		return (ft_error("Error : Unable to get textures."));
	if (!get_map(fd, &(data->map), nbtext))
		return (0);
	if (!get_portals(fd, &(data->map)))
		return (ft_error("Error : Portal format."));
	return (check_player_pos(&(data->eye), &(data->map)));
}
