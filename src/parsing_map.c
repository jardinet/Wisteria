/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:57:51 by mwragg            #+#    #+#             */
/*   Updated: 2020/06/24 16:56:58 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		check_block(t_block *block, t_map *map, int y, int x)
{
	int				i;
	unsigned int	maxid;

	block->isredirect = 0;
	block->nextx = 0;
	block->nexty = 0;
	block->rot = 0;
	block->iswall = ((block->texid & 255) != 0) * 1
	+ (((block->texid >> 8) & 255) != 0) * 2
	+ (((block->texid >> 16) & 255) != 0) * 4
	+ (((block->texid >> 24) & 255) != 0) * 8;
	if (((x == 0 || x == map->wid - 1) || (y == 0 || y == map->hei - 1))
		&& block->iswall != FULLBLOCK)
		return (-1);
	i = 0;
	maxid = 0;
	while (i < 4)
	{
		if (((block->texid >> (i * 8) & 255) > maxid))
			maxid = (block->texid >> (i * 8)) & 255;
		i++;
	}
	return (maxid);
}

int		check_map_line(t_map *map, int y, char *line, int nbtext)
{
	int	i;
	int	block;
	int	ret;

	i = 0;
	block = 0;
	ret = 0;
	while (line[i] && block < map->wid)
	{
		map->map[y][block].texid = (unsigned int)ft_atoi(line + i);
		ret = check_block(&(map->map[y][block]), map, y, block);
		if (ret < 0 || ret > nbtext)
			return (0);
		while (ft_isdigit(line[i]))
			i++;
		if ((line[i] != SPACE || i == 0) && line[i])
			return (0);
		block++;
		if (line[i])
			i++;
	}
	if (block != map->wid)
		return (0);
	return (1);
}

int		get_map(int fd, t_map *map, int nbtext)
{
	char	*line;
	int		i;

	if ((map->map = (t_block **)ft_calloc(sizeof(t_block*), map->hei)) == NULL)
		return (ft_error("Error : malloc(3) couldn't allocate sufficient "
		"memory."));
	i = 0;
	line = NULL;
	while (i < map->hei && get_next_line(fd, &line, 0) > 0)
	{
		if ((map->map[i] = (t_block *)ft_calloc(sizeof(t_block), map->wid))
		== NULL)
			return (ft_errordel("Error : malloc(3) couldn't allocate "
			"sufficient memory.", &line));
			if (!check_map_line(map, i, line, nbtext))
			return (ft_errordel("Error : Map format.", &line));
		ft_strdel(&line);
		i++;
	}
	if (i != map->hei)
		return (ft_error("Error : Map format."));
	return (1);
}
