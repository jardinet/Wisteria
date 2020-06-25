/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:59:03 by niboute           #+#    #+#             */
/*   Updated: 2018/12/04 17:13:58 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char				*ft_strstr(const char *str, const char *substr)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!*substr)
		return ((char*)str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == substr[j])
		{
			if (substr[j + 1] == 0x0)
				return ((char*)(str + i));
			j++;
		}
		i++;
	}
	return (0x0);
}
