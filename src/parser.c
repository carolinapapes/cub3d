/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:15 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 18:36:54 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_map(char *line, char ***map)
{
	char	*map_start;

	map_start = find_first_map_line(line);
	if (map_start == NULL || *map_start == '\0' || check_map(map_start) == 1)
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

int	check_elements(char **elements, t_start *start)
{
	// if (check_colours())
	if (ft_split_count(elements) < 9)
		return (1);
	if (check_four_dir(start, elements) == 1)
	{
		printf("falta path o hay alguno repetido\n");
		return (1);
	}
	printf("%s\n", start->n_fd);
	printf("%s\n", start->s_fd);
	printf("%s\n", start->w_fd);
	printf("%s\n", start->e_fd);
	free_line(&start->n_fd);
	free_line(&start->s_fd);
	free_line(&start->w_fd);
	free_line(&start->e_fd);
	//	if (check_textures(elements) == 1)
	//	return (1);
	return (0);
}

int	parse_elements(char *line, char ***elements, t_start *start)
{
	*elements = ft_split(line, '\n');
	if (!*elements)
		return (1);
	if (check_elements(*elements, start) == 1)
	{
		free_char_array(elements);
		return (1);
	}
	// find map start and check for empty lines
	// return (ft_split_free(file_lines), NULL);
	// write(1, map_start, ft_strlen(map_start));
	return (0);
}

int	parser_controler(int argc, char **argv, t_start *start)
{
	char	*line;
	char	**map;
	char	**elements;

	line = NULL;
	map = NULL;
	elements = NULL;
	if (argc != 2)
		return (1);
	if (check_file_extension(argv[1]) == EXIT_FAILURE)
		return (1);
	if (read_file(argv[1], &line) == 1)
		return (1);
	if (parse_map(line, &map) == 1)
	{
		free(line);
		return (1);
	}
	if (parse_elements(line, &elements, start) == 1)
	{
		free(line);
		free_char_array(&map);
		return (1);
	}
	if (start_initializer(start, map, elements) == 1)
	{
		free(line);
		free_char_array(&map);
		free_char_array(&elements);
		return (1);
	}
	free(line);
	free_char_array(&map);
	free_char_array(&elements);
	return (0);
}
