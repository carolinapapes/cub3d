/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:13:18 by kkoval            #+#    #+#             */
/*   Updated: 2025/02/23 16:56:09 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_map_start(char **file)
{
	int	l;
	int	i;
	int	start;
	int	valid;

	l = 0;
	start = -1;
	while (file[l] != NULL)
	{
		i = 0;
		valid = 0;
		while (file[l][i] != '\0')
		{
			if (is_map_character(file[l][i]) == 1)
			{
				start = -1;
				break ;
			}
			if (file[l][i] != ' ')
				valid = 1;
			i++;
		}
		if (file[l][i] == '\0' && valid == 1 && start == -1)
			start = l;
		l++;
	}
	return (start);
}

int	check_empty_lines_in_map(char **file)
{
	int	line;
	int	i;

	line = ft_map_start(file);
	printf("el mapa empieza aki%d\n", line);
	if (line == -1)
		return (1);
	while (file[line] != NULL)
	{
		printf("me he quedado atascado\n");
		i = 0;
		while (file[line][i] != '\0')
		{
			if (file[line][0] == ' ')
			{
				while (file[line][i] != '\0' && file[line][i] == ' ')
					i++;
				if (file[line][i] == '\0')
					return (1);
				else
					break ;
			}
			i++;
		}
		line++;
	}
	return (0);
}
