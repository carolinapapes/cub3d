/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:47:31 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 15:54:59 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_minipoint(t_vector point, int color)
{
	int			width;
	int			height;
	int			x;
	int			y;
	mlx_image_t	*aux;

	aux = get_miniview();
	if (point.x < 0 || point.x >= WINDOW_SIZE || point.y < 0
		|| point.y >= WINDOW_SIZE)
		return ;
	width = 5;
	while (width-- > -5)
	{
		height = 5;
		while (height-- > -5)
		{
			x = point.x + width;
			y = point.y + height;
			if (x >= 0 && x < WINDOW_SIZE && y >= 0 && y < WINDOW_SIZE)
				mlx_put_pixel(aux, x, y, color);
		}
	}
}

void	draw_miniline(t_vector origin, t_vector direction, int len, int color)
{
	t_vector	pixel;
	mlx_image_t	*image;

	image = get_miniview();
	len = abs(len);
	if (len < 0)
		return ;
	while (len--)
	{
		pixel.x = origin.x + direction.x * len;
		pixel.y = origin.y + direction.y * len;
		if (pixel.x < 0 || pixel.x >= WINDOW_SIZE || pixel.y < 0
			|| pixel.y >= WINDOW_SIZE)
			continue ;
		set_pixel(image, pixel, color);
	}
}

void	draw_miniray(t_vector_full vector, int color)
{
	draw_miniline(vector.origin, vector.direction, vector.distance, color);
	draw_minipoint(vector.end, color);
}

void	draw_tile(t_vector coord)
{
	mlx_image_t	*view;
	int			width;
	int			height;

	view = get_minimap();
	coord.x *= GRID_SIZE;
	coord.y *= GRID_SIZE;
	if ((uint32_t)(coord.x + GRID_SIZE) > view->width
		|| (uint32_t)(coord.y + GRID_SIZE) > view->height)
		return ;
	width = -1;
	while (width++ < GRID_SIZE)
	{
		height = -1;
		while (height++ < GRID_SIZE)
			mlx_put_pixel(view, coord.x + width, coord.y + height, HEX_WALL - 0x60606060);
	}
}
