/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:31:53 by kate              #+#    #+#             */
/*   Updated: 2025/02/23 19:27:15 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	map_x_size(char **map)
{
	int	size;
	int	max_size;
	int	i;

	max_size = 0;
	while(*map != NULL)
	{
		size = 0;
		i = 0;
		while((*map)[i] != '\0')
		{
			size++;
			i++;
		}
		if (size < 3)
			return (-1);
		if (size > max_size)
			max_size = size;
		map++;
	}
	return (max_size);
}

int	map_y_size(char **map)
{
	int	size;

	size = 0;
	while(*map != NULL)
	{
		size++;
		map++;
	}
	if (size < 3)
		return (-1);
	return (size);
}

int	get_map_value(char c, t_start *start, int x, int y)
{
	if (c == '1')
		return (1);
	if (c == '0')
		return (0);
	if (c == ' ')
		return (3);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		start->player_dir = c;
		start->player_pos.x = x;
		start->player_pos.y = y;
		return (0);
	}
	return (-2);
}

void	fill_map_row(int *map_row, char *map_line, int size_x, t_start *start, int y)
{
	int	x;

	x = 0;
	while (map_line[x] != '\0' && x < size_x)
	{
		map_row[x] = get_map_value(map_line[x], start, x, y);
		x++;
	}
	while (x < size_x)
	{
		map_row[x] = 3;
		x++;
	}
}

int	**char_to_int(char **map, int size_x, int size_y, t_start *start)
{
	int	**map_arr;
	int	y;

	map_arr = malloc(sizeof(int *) * size_y);
	if (!map_arr)
		return (NULL);
	y = 0;
	while (y < size_y)
	{
		map_arr[y] = malloc(sizeof(int) * size_x);
		if (!map_arr[y])
		{
			while (--y >= 0)
				free(map_arr[y]);
			free(map_arr);
			return (NULL);
		}
		fill_map_row(map_arr[y], map[y], size_x, start, y);
		y++;
	}
	return (map_arr);
}


//TODO temporary function, delete later
void	print_int_map(int **arr, int size_x, int size_y)
{
	int y;
	int	x;

	y = 0;
	while(y < size_y)
	{
		x = 0;
		while (x < size_x)
		{
			printf("%d", arr[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}




int	start_map(t_start *start, char **map)
{
	//inicializar el size cord
	int	size_x;
	int	size_y;

	size_x = map_x_size(map);
	size_y = map_y_size(map);
	if (size_y == -1 || size_x == -1)
	{
		printf("map error, the size of x or y too small\n"); // TODO delete later
		return (1);
	}
	start->map.size_int.x = size_x;
	start->map.size_int.y = size_y;
	start->map.map = map;
	ft_print_split(start->map.map); // TODO delete later

	start->map.map_int = char_to_int(map, size_x, size_y, start);
	if (start->map.map_int == NULL)
		return (1);
	print_int_map(start->map.map_int, size_x, size_y);// TODO delete later
	printf("\n\n");
	printf("x: %d\n, y: %d\n    y la letra es: %c\n", start->player_pos.x, start->player_pos.y, start->player_dir);
	fill_flood(start->map.map_int, start->player_pos.x, start->player_pos.y, start->map.size_int);
	if (check_fill_flood(start) == 1) //free start
	{
		printf("check fill flood ha encontrado error en el mapa\n");
		return (1);
	}
	printf("\n\n");
	print_int_map(start->map.map_int, size_x, size_y);
	return (0);
	
}

t_start	*start_initializer(char *line)
{
	t_start	*start;
	char	**map;
	char	**elements;

	map = get_map(line);
	if (!map)
		return(free_line(&line), NULL);
	elements = get_elements(line);
	if (!elements)
		return(free_line(&line), NULL);
	free(line);
	
	start = malloc(sizeof(t_start));
	if (!start)
		return (NULL);
	
	if (start_map(start, map) == 1)
	{
		printf("el mapa ha fallado\n");
		//free map
		//free elemnts
		return(free_start(start), NULL);
	}
	//start_textures(start, elements);
	//start_colour(start, elements);
	//start_player(start);
	//liberar elements y map!? Siii
	return (start);
}
