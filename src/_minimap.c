/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minimap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:50 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 19:27:46 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	g_map[16][16] = {\
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, \
	};

static int	is_wall(t_vector coord)
{
	int	x;
	int	y;

	x = (int)coord.x;
	y = (int)coord.y;
	if (x < 0 || x >= 16 || y < 0 || y >= 16)
		return (OUTSIDE);
	if (g_map[y][x] == WALL)
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

int	is_fixed_object(uint32_t x, uint32_t y, t_start *start)
{
	int			content;
	int			x_coor;
	int			y_coor;

	x_coor = x / GRID_SIZE;
	y_coor = y / GRID_SIZE;
	if (x_coor < 0 || x_coor >= 16 || y_coor < 0 || y_coor >= 16)
		return (WALL);
	if (x_coor >= start->map.size_int.x || y_coor >= start->map.size_int.y)
		return (WALL);
	content = start->map.map_int[y_coor][x_coor];
	if (x % GRID_SIZE == 0 || y % GRID_SIZE == 0)
		content |= GRID;
	return (content);
}

// BONUS FN
void	draw_minimap(mlx_image_t *image, uint32_t x, uint32_t y, t_start *start)
{
	int	content;

	content = is_fixed_object(x, y, start);
	if (content == GRID)
		mlx_put_pixel(image, x, y, HEX_GRID);
	if (content == WALL)
		mlx_put_pixel(image, x, y, HEX_WALL);
}

void	update_mlx_player(t_vector pos_delta)
{
	mlx_image_t	*mlx_player;

	mlx_player = get_player_image();
	mlx_player->instances[0].x += pos_delta.x;
	mlx_player->instances[0].y += pos_delta.y;
}
