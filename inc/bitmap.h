/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:20:06 by niboute           #+#    #+#             */
/*   Updated: 2020/06/14 15:34:09 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

# include <unistd.h>
# include <fcntl.h>
# include "../inc/header.h"

typedef struct			s_bmp_hd
{
	int					type;
	int					size;
	int					res1;
	int					res2;
	int					offset;
}						t_bmp_hd;

typedef struct			s_bmp_if
{
	unsigned int		size;
	int					width;
	int					height;
	unsigned short int	planes;
	unsigned short	int bits;
	unsigned int		compression;
	unsigned int		imgsize;
	int					xres;
	int					yres;
	unsigned int		nbcols;
	unsigned int		impcols;
}						t_bmp_if;

#endif
