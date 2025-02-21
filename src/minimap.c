/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:50 by capapes           #+#    #+#             */
/*   Updated: 2025/02/21 18:17:53 by capapes          ###   ########.fr       */
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
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
	{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, \
	};

int	is_fixed_object(uint32_t x, uint32_t y)
{
	int	content;
	int	x_coor;
	int	y_coor;

	x_coor = x / GRID_SIZE;
	y_coor = y / GRID_SIZE;
	content = g_map[y_coor][x_coor];
	if (x % GRID_SIZE == 0 || y % GRID_SIZE == 0)
		content |= GRID;
	return (content);
}

// BONUS FN
static void	draw_minimap(mlx_image_t *image, uint32_t x, uint32_t y)
{
	int	content;

	content = is_fixed_object(x, y);
	if (content & GRID)
		mlx_put_pixel(image, x, y, GRID_COLOR);
	if (content & WALL)
		mlx_put_pixel(image, x, y, WALL_COLOR);
}

// THIS FUNCTION WILL BE REMOVED AND REPLACED 
// BY THE PARSER RESULT CALL TO SET PLAYER
void	minimap_init(void)
{
	mlx_image_t	*minimap;

	minimap = new_image_full();
	iter_image(minimap, draw_minimap);
}
