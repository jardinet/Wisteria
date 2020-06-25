/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:37:04 by niboute           #+#    #+#             */
/*   Updated: 2020/06/25 11:56:24 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../inc/bitmap.h"

int			main(int ac, char **argv)
{
	t_wolf	data;

	if (ac != 2)
		ft_strexit("Error : Invalid number of arguments.");
	ft_bzero(&data, sizeof(t_wolf));
	if (!parsing(argv[1], &data))
		wipeout(&data, EXIT_FAILURE);
	if (!init_sdl(&data.win))
		wipeout(&data, EXIT_FAILURE);
	init_camera(&data.eye, &data.plane);
	loop(&data);
	wipeout(&data, EXIT_SUCCESS);
	return (0);
}
