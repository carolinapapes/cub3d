/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minimap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:50 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 18:17:34 by capapes          ###   ########.fr       */
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

int	is_axis_wall(t_vector axis_positive, t_axis axis, t_vector_full ray)
{
	t_vector	axis_negative;
	int			res;

	axis_positive.x = axis_positive.x / GRID_SIZE;
	axis_positive.y = axis_positive.y / GRID_SIZE;
	axis_negative = axis_positive;
	axis_negative.arr[axis] = axis_negative.arr[axis] - 1;
	if (ray.quadrant.arr[axis] == 1)
	{
		if (is_wall(axis_negative) == WALL)
			return (WALL);
		res = is_wall(axis_positive);
		return (res);
	}
	res = is_wall(axis_positive);
	if (res == WALL)
		return (res);
	res = is_wall(axis_negative);
	return (res);
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

void	draw_minimap(t_vector coord)
{
	int			content;
	mlx_image_t	*image;

	image = get_minimap_image();
	content = is_fixed_object(coord);
	if (content == OUTSIDE)
		return ;
	if (coord.x && coord.y)
		mlx_put_pixel(image, (uint32_t)coord.x * GRID_SIZE,
			(uint32_t)coord.y * GRID_SIZE, HEX_GRID);
	if (content == WALL)
		coordinate_paint((int)coord.x, (int)coord.y);
}

void	update_mlx_miniplayer_pos(t_vector position, int axis)
{
	mlx_image_t	*mlx_player;

	mlx_player = get_miniplayer_image();
	if (axis == Y)
		mlx_player->instances[0].y += position.y;
	if (axis == X)
		mlx_player->instances[0].x += position.x;
}

void	update_mlx_miniview_position(t_vector pos_delta, int axis)
{
	mlx_image_t	*mlx_aux;

	mlx_aux = get_miniview_image();
	if (axis == Y)
		mlx_aux->instances[0].y += pos_delta.y;
	if (axis == X)
		mlx_aux->instances[0].x += pos_delta.x;
}
