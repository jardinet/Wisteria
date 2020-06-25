/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:52:52 by niboute           #+#    #+#             */
/*   Updated: 2020/06/23 21:44:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

t_file				*create_destroy_file(int act, const int fd, t_file **files)
{
	t_file	*new;
	t_file	*tmp;

	if (act)
	{
		if (!(new = (t_file*)malloc(sizeof(t_file))))
			return (NULL);
		new->next = *files;
		*(new->buff) = '\0';
		*files = new;
		return (new);
	}
	new = *files;
	if (new->fd == fd)
	{
		*files = new->next;
		ft_memdel((void**)&new);
		return (*files);
	}
	while (new->next && new->next->fd != fd)
		new = new->next;
	tmp = new->next;
	new->next = (new->next ? new->next->next : NULL);
	ft_memdel((void**)&tmp);
	return (*files);
}

int					ft_copy_line(char **save, t_line *line, char *buff,
		size_t size)
{
	t_line	*tmp;
	size_t	clen;

	if (!(*save = (char*)malloc(size + 1)))
		return (0);
	**save = '\0';
	while (line)
	{
		tmp = line;
		ft_strcat(*save, line->buff);
		line = line->next;
		ft_memdel((void**)&tmp);
	}
	if (buff)
	{
		clen = ft_strclen(buff, '\n');
		ft_strncat(*save, buff, clen);
		(*save)[size] = '\0';
	}
	return (1);
}

int					ft_add_line(t_line **line, char *str)
{
	t_line			*newline;
	t_line			*ptr;

	if (!(newline = (t_line*)malloc(sizeof(t_line))))
		return (-1);
	ft_strcpy(newline->buff, str);
	newline->next = NULL;
	if (!*line)
		*line = newline;
	else
	{
		ptr = *line;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = newline;
	}
	return (1);
}

int					read_next_line(t_file *file, char **save, size_t size)
{
	t_line			*line;
	int				ret;

	line = NULL;
	*save = NULL;
	ret = ft_strclen(file->buff, '\n');
	while (!(ft_strchr(file->buff, '\n')))
	{
		size += ret;
		if (ft_strlen(file->buff) != 0)
			ft_add_line(&line, file->buff);
		ret = read(file->fd, file->buff, BUFF_SIZE);
		if (ret > 0)
			file->buff[ret] = '\0';
		else
		{
			if (size)
				ft_copy_line(save, line, NULL, size);
			return (size ? 1 : ret);
		}
	}
	ft_copy_line(save, line, file->buff, size + ft_strclen(file->buff, '\n'));
	line = NULL;
	return (1);
}

int					get_next_line(const int fd, char **line,
					unsigned int destroy)
{
	static t_file	*files = NULL;
	int				found;
	t_file			*ptr;
	size_t			size;

	if (destroy)
		return (destroy_gnl_files(&files));
	if (fd < 0 || !line || read(fd, NULL, 0) < 0)
		return (-1);
	ptr = files;
	while (ptr && ptr->fd != fd)
		ptr = ptr->next;
	found = (ptr && ptr->fd == fd) ? 1 : 0;
	if (!found && !(ptr = create_destroy_file(1, fd, &files)))
		return (-1);
	if (!found)
		files->fd = fd;
	found = read_next_line(ptr, line, 0);
	size = ft_strclen(ptr->buff, '\n');
	ft_strcpy(ptr->buff, ptr->buff + size + (ptr->buff[size] == '\n' ? 1 : 0));
	if (found > 0)
		return (found);
	create_destroy_file(0, fd, &files);
	return (found);
}
