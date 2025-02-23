/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:15 by capapes           #+#    #+#             */
/*   Updated: 2025/02/23 01:20:55 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char **get_map(char *line)
{
	char **map;
	char *map_start;
	map_start = find_first_map_line(line);
	if (map_start == NULL || *map_start == '\0' || check_map(map_start) == 1)
		return (NULL);
	map = ft_split(map_start, '\n');
	if (check_empty_lines_in_map(map) == 1)
	{
		printf("lineas vacias en el map\n");
		return (ft_split_free(map), NULL);
	}
	return map;

}

int	check_elements(char **elements)
{
	//if (check_textures(elements) == 1)
	//	return (1);
	if (ft_split_count(elements) < 9)
		return (1);
	return (0);
}

char	**get_elements(char *line)
{
	char	**elements;

	elements = ft_split(line, '\n');
	if (!elements)
		return (ft_split_free(elements), NULL);
	
	//if (check_elements(elements) == 1)
		//return (ft_split_free(elements), NULL);
	

	//find map start and check for empty lines
		//return (ft_split_free(file_lines), NULL);
	//write(1, map_start, ft_strlen(map_start));
	
	return (elements);
}

t_start	*parser_controler(int argc, char **argv)
{
	t_start	*start;
	char	*line;

	if (argc != 2)
		return (NULL);
	if (check_file_extension(argv[1]) == EXIT_FAILURE)
		return (NULL);
	line = read_file(argv[1]);
	if (line == NULL)
		return (NULL);
	//more serious check for path and closed map
	start = start_initializer(line);
	return (start);
}
