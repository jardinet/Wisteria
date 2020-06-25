/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_portals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 17:00:15 by mwragg            #+#    #+#             */
/*   Updated: 2020/06/24 16:34:59 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		skip_to_number(char *line, int *i, int endl)
{
	if (line[*i] == '-' && !ft_isdigit(line[*i + 1]))
		return (0);
	if (line[*i] == '-')
		(*i)++;
	while (ft_isdigit(line[*i]))
		(*i)++;
	if ((line[*i] != SPACE && !endl) || (endl && line[*i] != '\0'))
		return (0);
	if (!endl)
		(*i)++;
	if (!(line[*i] == '-' && ft_isdigit(line[*i + 1]))
		&& !ft_isdigit(line[*i]) && !endl)
		return (0);
	return (1);
}

int		check_portal(t_block *block, t_map *map, int y, int x)
{
	if (block->isredirect > 15 || block->isredirect == 0)
		return (0);
	if ((block->nextx + x) <= 0 || (block->nextx + x) > (map->wid - 2))
		return (0);
	if ((block->nexty + y) <= 0 || (block->nexty + y) > (map->hei - 2))
		return (0);
	if (block->rot > 3)
		return (0);
	return (1);
}

int		assign_portal_values(char *line, int *i, t_map *map)
{
	int	y;
	int	x;

	y = ft_atoi(line);
	if (!skip_to_number(line, i, FALSE))
		return (0);
	x = ft_atoi(line + *i);
	if (!skip_to_number(line, i, FALSE))
		return (0);
	if (y < 1 || y > (map->hei - 2) || x < 1 || x > (map->wid - 2))
		return (0);
	map->map[y][x].isredirect = ft_atoi(line + *i);
	if (!skip_to_number(line, i, FALSE))
		return (0);
	map->map[y][x].nexty = ft_atoi(line + *i);
	if (!skip_to_number(line, i, FALSE))
		return (0);
	map->map[y][x].nextx = ft_atoi(line + *i);
	if (!skip_to_number(line, i, FALSE))
		return (0);
	map->map[y][x].rot = ft_atoi(line + *i);
	if (!skip_to_number(line, i, TRUE))
		return (0);
	return (check_portal(&(map->map[y][x]), map, y, x));
}

int		parsing_portals(int fd, t_map *map, int nbpor)
{
	char	*line;
	int		i;
	int		ret;

	line = NULL;
	while (nbpor > 0 && (ret = get_next_line(fd, &line, 0)) > 0)
	{
		i = 0;
		if (ft_count_words(line, SPACE) != 6 || !ft_isdigit(line[0])
			|| !assign_portal_values(line, &i, map))
		{
			ft_strdel(&line);
			return (0);
		}
		nbpor--;
		ft_strdel(&line);
	}
	if (nbpor != 0)
		return (0);
	if (ret != 0 && get_next_line(fd, &line, 0) != 0)
		return (0);
	return (1);
}

int		get_portals(int fd, t_map *map)
{
	char	*line;
	int		nbpor;
	int		i;
	int		ret;

	line = NULL;
	if ((ret = get_next_line(fd, &line, 0)) < 1)
		return (0);
	nbpor = ft_atoi(line);
	i = 0;
	while (ft_isdigit(line[i]) && i < 3)
		i++;
	if (line[i] != '\0' || nbpor > ((map->hei * map->wid) / 2))
	{
		ft_strdel(&line);
		return (0);
	}
	ft_strdel(&line);
	if (nbpor == 0)
		return (1);
	return (parsing_portals(fd, map, nbpor));
}
