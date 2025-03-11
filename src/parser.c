/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:15 by capapes           #+#    #+#             */
/*   Updated: 2025/03/11 03:03:15 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	empty_string(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (1);
		line++;
	}
	return (0);
}

int	check_variables(t_start *start)
{
	if (start->n_fd == NULL || start->s_fd == NULL || start->e_fd == NULL || start->w_fd == NULL ) // ha faltado una textura
		return (1);
	//if (start->ceiling.rgba == 0 || start->floor.rgba == 0) 
		//return (1);
	return (0);
}

int	check_elements(char **elements, t_start *start)
{
	int	y;

	y = 0;
	if (ft_split_count(elements) < 9)
		return (1);
	while (elements[y] != NULL) // en realidad solo hasta start de map
	{
		if (empty_string(elements[y]) == 0)
			return (1);
		if (is_texture(elements[y], start) == 1)
		{
			if (is_color(elements[y], start) == 1)
				return (1);
		}
		y++;
	}
	if (check_variables(start) == 1) // algun elemento ha fallado
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
		free_char_array(elements);
		free_line(&start->n_fd);
		free_line(&start->s_fd);
		free_line(&start->w_fd);
		free_line(&start->e_fd);
		return (1);
	}
	return (0);
}

//limpiar ese desproposito de frees
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
	{
		free(line);
		return (1);
	}
	if (parse_elements(line, &elements, start) == 1)
	{
		printf("no he entrado en el initiliazer\n");
		free(line);
		free_char_array(&map);
		return (1);
	}
	printf("%s\n", start->n_fd);
	printf("%s\n", start->s_fd);
	printf("%s\n", start->w_fd);
	printf("%s\n", start->e_fd);
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
