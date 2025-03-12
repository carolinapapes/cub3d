/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:36:01 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/12 16:25:02 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	fill_flood(int	**arr, int x, int y, t_int_pair size)
{
	if (x >= size.x || x < 0 || y >= size.y || y < 0)
		return ;
	if (arr[y][x] == 5 || arr[y][x] == 1 || arr[y][x] == 3)
		return ;
	if (arr[y][x] == 0)
		arr[y][x] = 5;
	fill_flood(arr, x, y - 1, size);
	fill_flood(arr, x, y + 1, size);
	fill_flood(arr, x + 1, y, size);
	fill_flood(arr, x - 1, y, size);
}

int	check_borders(t_start *start)
{
	int	size_x;
	int	size_y;
	int	x;
	int	y;

	size_x = start->map.size_int.x;
	size_y = start->map.size_int.y;
	y = 0;
	while (y < size_y)
	{
		if (start->map.map_int[y][0] == 5 || \
			start->map.map_int[y][size_x - 1] == 5)
			return (1);
		y++;
	}
	x = 0;
	while (x < size_x)
	{
		if (start->map.map_int[0][x] == 5 || \
			start->map.map_int[size_y - 1][x] == 5)
			return (1);
		x++;
	}
	return (0);
}

int	check_padding(t_start *start)
{
	int	**map;
	int	size_x;
	int	size_y;
	int	x;
	int	y;

	map = start->map.map_int;
	size_x = start->map.size_int.x;
	size_y = start->map.size_int.y;
	y = -1;
	while (++y < size_y - 1)
	{
		x = 1;
		while (x < size_x - 1)
		{
			if (map[y][x] == 5)
			{
				if (map[y + 1][x] == 3 || map[y - 1][x] == 3 \
					|| map[y][x + 1] == 3 || map[y][x - 1] == 3)
					return (1);
			}
			x++;
		}
	}
	return (0);
}

int	check_fill_flood(t_start *start)
{
	if (check_borders(start) == 1)
		return (1);
	if (check_padding(start) == 1)
		return (1);
	return (0);
}
