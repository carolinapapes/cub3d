/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:13:18 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/12 20:30:20 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	check_for_newlines_in_map(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			i++;
			if (map[i] == '\0')
				return (0);
			if (map[i] == '\n')
			{
				while (map[i] == '\n')
					i++;
				if (map[i] == '\0')
					return (0);
				else
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	is_valid_map_line(char *line)
{
	int	i;
	int	has_non_space;

	i = 0;
	has_non_space = 0;
	while (line[i] != '\0')
	{
		if (is_map_character(line[i]))
			return (-1);
		if (line[i] != ' ')
			has_non_space = 1;
		i++;
	}
	if (has_non_space)
		return (0);
	return (1);
}

int	ft_map_start(char **file)
{
	int	l;
	int	start;
	int	valid;

	l = 0;
	start = -1;
	while (file[l] != NULL)
	{
		valid = is_valid_map_line(file[l]);
		if (valid == 0 && start == -1)
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
	if (line == -1)
		return (1);
	while (file[line] != NULL)
	{
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
