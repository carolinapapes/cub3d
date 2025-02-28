/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minimap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:50 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 01:29:46 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	is_wall(t_vector coord)
{
	int		x;
	int		y;
	t_start	*start;

	start = get_start();
	x = (int)coord.x;
	y = (int)coord.y;
	if (x < 0 || y < 0
		|| x >= start->map.size_int.x || y >= start->map.size_int.y)
		return (OUTSIDE);
	if (start->map.map_int[y][x] == WALL)
		return (WALL);
	return (GRID);
}

int	is_axis_wall(t_vector coord, t_axis axis, t_vector_full ray)
{
	t_vector	prev;
	int			dir;
	int			prev_res;
	int			res;

	dir = ray.quadrant.arr[axis];
	coord.x = coord.x / GRID_SIZE;
	coord.y = coord.y / GRID_SIZE;
	prev = coord;
	prev.arr[axis] = prev.arr[axis] - 1;
	if (dir == 1)
	{
		prev_res = is_wall(prev);
		if (prev_res == WALL)
			return (prev_res);
		res = is_wall(coord);
		return (res);
	}
	res = is_wall(coord);
	if (res == WALL)
		return (res);
	prev_res = is_wall(prev);
	return (prev_res);
}

int	is_fixed_object(t_vector coord)
{
	int			content;
	t_start		*start;

	start = get_start();
	if (coord.x >= start->map.size_int.x || coord.y >= start->map.size_int.y)
		return (OUTSIDE);
	content = start->map.map_int[(int)coord.y][(int)coord.x];
	return (content);
}

void	iter_map(void fn(t_vector))
{
	t_vector	coord;
	t_start		*start;
	double		cell_quantity;
	double		current_cell;

	coord.y = 0;
	coord.x = 0;
	start = get_start();
	current_cell = 0;
	cell_quantity = start->map.size_int.x * start->map.size_int.y;
	while (current_cell < cell_quantity)
	{
		if (coord.x >= start->map.size_int.x)
		{
			coord.x = 0;
			coord.y++;
		}
		fn(coord);
		coord.x++;
		current_cell++;
	}
}

void	draw_minimap(t_vector coord)
{
	int			content;
	mlx_image_t	*image;

	image = get_minimap_image();
	content = is_fixed_object(coord);
	mlx_put_pixel(image, (uint32_t)coord.x * GRID_SIZE,
		(u_int32_t)coord.y * GRID_SIZE, HEX_GRID);
	if (content == WALL)
		coordinate_paint((int)coord.x, (int)coord.y);
}

void	update_mlx_player(t_vector pos_delta, int axis)
{
	mlx_image_t	*mlx_player;

	mlx_player = get_player_image();
	if (axis == Y)
		mlx_player->instances[0].y += pos_delta.y;
	if (axis == X)
		mlx_player->instances[0].x += pos_delta.x;
}
