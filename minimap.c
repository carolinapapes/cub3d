/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:50 by capapes           #+#    #+#             */
/*   Updated: 2025/02/11 18:05:54 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <string.h>

int		map[16][16] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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

void	set_minimap(mlx_t *mlx)
{
	mlx_image_t	*image;

	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	iter_image(image, add_minimap);
	if (mlx_image_to_window(mlx, image, 0, HEIGHT) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return ;
	}
	set_player(mlx, 8, 8);
}
