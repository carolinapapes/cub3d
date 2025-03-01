/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:04:26 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/01 04:28:33 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_map_character(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W' \
	|| c == 'E')
		return (0);
	return (1);
}

int	is_one_view(char *map)
{
	int	letter_count;

	letter_count = 0;
	while (*map)
	{
		if (*map == 'N' || *map == 'S' || *map == 'W' || *map == 'E')
			letter_count++;
		if (letter_count > 1)
			return (1);
		map++;
	}
	if (letter_count != 1)
		return (1);
	return (0);
}

char	*find_first_map_line(char *input)
{
	int		i;

	while (*input)
	{
		while (*input != '\n')
			input++;
		while (*input == '\n')
			input++;
		i = 0;
		while (input[i] != '\0' && (is_map_character(input[i]) == 0 \
			|| input[i] == '\n'))
			i++;
		if (input[i] == '\0' && i != 0)
			return (input);
		input = &input[i];
	}
	return (NULL);
}

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

int	check_map(char *line_map)
{
	if (is_one_view(line_map) == 1)
	{
		printf("There are more that one direction\n"); // TODO delete later
		return (1);
	}
	if (check_for_newlines_in_map(line_map) == 1)
	{
		printf("%d  consecutive enter", check_for_newlines_in_map(line_map)); // TODO delete
		return (1);
	}
	return (0);
}
