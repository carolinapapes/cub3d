/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:15 by capapes           #+#    #+#             */
/*   Updated: 2025/03/11 18:52:01 by kkoval           ###   ########.fr       */
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
	if (start->n_fd == NULL || start->s_fd == NULL || start->e_fd == NULL || start->w_fd == NULL )
	{
		printf("ha fallado textura\n"); //TODO delete check
		return (1);
	}
	if (start->ceiling.rgba == 0 || start->floor.rgba == 0)
	{
		if (start->ceiling.rgba == 0) //TODO delete check
			printf("ceiling no tiene color\n");
		if (start->floor.rgba == 0)
			printf("floor no tiene color\n");
		return (1);
	}
	return (0);
}

int	check_elements(char **elements, t_start *start)
{
	int	y;

	y = 0;
	if (ft_split_count(elements) < 9)
		return (1);
	while (y < 6) // en realidad solo hasta start de map
	{
		if (empty_string(elements[y]) == 0) //creo que ya es inecesario porque el parseo del mapa se lo carga
		{
			printf("spaces en enter en linea num: %d\n", y);
			return (1);
		}
		
		if (is_texture(elements[y], start) == 0)
			printf("esto ha entrado en textura %s\n", elements[y]);
		else
		{
			if (is_texture(elements[y], start) == -1)
			{
				printf("textura repetida\n");
				return (1);
			}
			printf("esto no ha entrado en textura %s\n", elements[y]);
			if (is_color(elements[y], start) == 1)
			{
				printf("esto no ha pasado el check de color\n");
				return (1);
			}
				
		}
		y++;
	}
	if (check_variables(start) == 1) // algun elemento ha fallado
	{	
		printf("ha habido fallo en check var\n");
		return (1);
	}
	
	return (0);
}

int	parse_elements(char *line, char ***elements, t_start *start)
{
	*elements = ft_split(line, '\n');
	if (!*elements)
		return (1);
	if (check_elements(*elements, start) == 1)
	{
		printf("problema en check elements\n");
		free_char_array(elements);
		free_line(&start->n_fd);
		free_line(&start->s_fd);
		free_line(&start->w_fd);
		free_line(&start->e_fd);
		return (1);
	}
	return (0);
}

int	free_parser(char *line, char **map, char **elements)
{
	free_line(&line);
	free_char_array(&map);
	free_char_array(&elements);
	return (1);
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
		printf("ha habido un problema en mapa\n");
		return (free_parser(line, map, elements));
	}
	if (parse_elements(line, &elements, start) == 1)
	{
		printf("no he entrado en el initiliazer\n");
		return (free_parser(line, map, elements));
	}
	printf("antes del init\n");
	if (start_initializer(start, map, elements) == 1)
	{
		printf("ha fallado initiliazer\n");
		return (free_parser(line, map, elements));
	}
	free_parser(line, map, elements);
	return (0);
}
