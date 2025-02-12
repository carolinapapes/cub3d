/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:50 by capapes           #+#    #+#             */
/*   Updated: 2025/02/12 21:25:42 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		map[16][16] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, PLAYER, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int	is_fixed_object(uint32_t x, uint32_t y)
{
	int	content;
	int	x_coor;
	int	y_coor;

	x_coor = x / GRID_SIZE;
	y_coor = y / GRID_SIZE;
	content = map[y_coor][x_coor];
	if (x % GRID_SIZE == 0 || y % GRID_SIZE == 0)
		content |= GRID;
	return (content);
}

void	add_minimap(mlx_image_t *image, uint32_t x, uint32_t y)
{
	int	content;

	content = is_fixed_object(x, y);
	if (content & GRID)
		mlx_put_pixel(image, x, y, GRID_COLOR);
	if (content & WALL)
		mlx_put_pixel(image, x, y, WALL_COLOR);
}

void	map_add_player(mlx_t *mlx)
{
	int	pos[2];

	pos[Y] = MAP_SIZE_Y;
	while (pos[Y]--)
	{
		pos[X] = MAP_SIZE_X;
		while (pos[X]--)
		{
			if (map[pos[Y]][pos[X]] == PLAYER)
			{
				set_player(mlx, pos[X], pos[Y]);
				return ;
			}
		}
	}
	return ;
}

void	set_minimap(mlx_t *mlx)
{
	mlx_image_t	*image;

	image = mlx_add_image(mlx, WIDTH, HEIGHT, (int[]){0, HEIGHT});
	iter_image(image, add_minimap);
	map_add_player(mlx);
}
