/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:50 by capapes           #+#    #+#             */
/*   Updated: 2025/02/06 17:13:29 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>

static int	is_minimap(uint32_t x, uint32_t y)
{
	int	content;
	int	len;
	int	x_coor;
	int	y_coor;

	int map[16][16] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};
	len = 32;
	x_coor = x / len;
	y_coor = y / len;
	if (x_coor < 0 || x_coor > 15 || y_coor < 0 || y_coor > 15)
		return (0);
	content = map[y_coor][x_coor];
	printf("%d\t", content);
	if (content)
		return (content);
	if (x % len == 0 || y % len == 0)
		return (GRID);
	return (0);
}

static int	get_color(int content)
{
	if (content == GRID)
		return (ft_pixel(180, 180, 180, 180));
	if (content == WALL)
		return (ft_pixel(255, 255, 255, 255));
	if (content == ITEM)
		return (ft_pixel(255, 0, 0, 255));
	if (content == PLAYER)
		return (ft_pixel(0, 255, 0, 255));
	return (0);
}

void	*add_minimap(mlx_image_t *image, uint32_t x, uint32_t y, void *param)
{
	uint32_t	color;

	param = (int *)param;
	color = 0;
	if (y > HEIGHT / 2)
		get_color(is_minimap(x, y - HEIGHT / 2));
	if (color != 0)
		mlx_put_pixel(image, x, y, color);
	return (NULL);
}
