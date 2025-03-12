/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:15 by capapes           #+#    #+#             */
/*   Updated: 2025/03/12 20:30:52 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	parse_map(char *line, char ***map)
{
	char	*map_start;

	map_start = find_first_map_line(line);
	if (map_start == NULL || check_map(map_start) == 1)
		return (1);
	*map = ft_split(map_start, '\n');
	if (!*map)
		return (1);
	if (check_empty_lines_in_map(*map) == 1)
	{
		free_char_array(map);
		return (1);
	}
	return (0);
}

int	check_variables(t_start *start)
{
	if (start->n_fd == NULL || start->s_fd == NULL || start->e_fd == NULL \
		|| start->w_fd == NULL )
		return (1);
	if (start->ceiling.repeated == 1 || start->floor.repeated == -1)
		return (1);
	printf("no ha habido problemas en var check\n"); //delete later
	return (0);
}

int	check_elements(char **elements, t_start *start)
{
	int	y;
	int	res;

	y = 0;
	if (ft_split_count(elements) < 9)
		return (1);
	while (elements[y] != NULL)
	{
		if (line_in_map(elements[y], ft_strlen(elements[y])) == 0)
			break ;
		res = is_texture(elements[y], start);
		if (res == -1)
			return (1);
		else if (res == 1)
		{
			if (is_color(elements[y], start) == 1)
				return (1);
		}
		y++;
	}
	if (check_variables(start) == 1)
		return (1);
	return (0);
}

int	parse_elements(char *line, char ***elements, t_start *start)
{
	*elements = ft_split(line, '\n');
	if (!*elements)
		return (1);
	if (check_elements(*elements, start) == 1)
	{
		free_line(&start->n_fd);
		free_line(&start->s_fd);
		free_line(&start->w_fd);
		free_line(&start->e_fd);
		return (1);
	}
	return (0);
}

int	parser_controler(char *file, t_start *start)
{
	char	*line;
	char	**map;
	char	**elements;

	map = NULL;
	line = NULL;
	elements = NULL;
	line = extract_content(file);
	if (line == NULL)
		return (1);
	if (parse_map(line, &map) == 1)
		return (free_parser(line, map, elements));
	if (parse_elements(line, &elements, start) == 1)
		return (free_parser(line, map, elements));
	printf("he pasado check_elements\n"); //delete later
	if (start_map(start, map) == 1)
		return (free_parser(line, map, elements));
	printf("he pasado start_map\n"); //delete later
	free_parser(line, map, elements);
	return (0);
}
