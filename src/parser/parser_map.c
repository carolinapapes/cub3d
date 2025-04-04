/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:04:26 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/13 19:40:58 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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

int	line_in_map(char *line, int len)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && i < len)
	{
		if (is_map_character(line[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	*find_first_map_line(char *input)
{
	int	i;

	while (*input)
	{
		i = 0;
		while (input[i] && input[i] != '\n')
			i++;
		if (!input[i])
			return (NULL);
		if (line_in_map(input, i) == 0 && i > 0)
			return (input);
		input = &input[i + 1];
	}
	return (NULL);
}

int	check_map(char *line_map)
{
	if (is_one_view(line_map) == 1)
		return (1);
	if (check_for_newlines_in_map(line_map) == 1)
		return (1);
	return (0);
}
