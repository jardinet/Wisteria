/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_check_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:24:58 by niboute           #+#    #+#             */
/*   Updated: 2020/06/06 20:37:25 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int			ft_read_check_input(char *text, char *error, void *data,
			int (*fct)(char*, void*))
{
	int		ret;
	char	buff[INPUT_SIZE + 1];
	int		validinput;

	validinput = 0;
	while (!validinput)
	{
		ft_putendl(text);
		ft_putstr(WR_MAG"Type \"quit\" to leave prompt. PS: The program will"
		" exit if you didn't enter a valid input beforehand\n" WR_RESET);
		ret = read(0, buff, INPUT_SIZE);
		buff[ret] = '\0';
		if (!ft_strncmp(buff, "quit", 4))
			return (1);
		validinput = fct(buff, data);
		if (!validinput)
		{
			ft_putstr(WR_RED);
			ft_putstr(error);
			ft_putstr(WR_RESET);
		}
	}
	return (0);
}
