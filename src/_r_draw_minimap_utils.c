/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _r_draw_minimap_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:18:39 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 18:02:11 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_intersect(t_vector_full vector, int color)
{
	t_vector	constants;

	constants = game_constants().limit_movement;
	if (vector.origin.x > constants.x)
	{
		vector.origin.x = constants.x;
		vector.end.x += constants.x * vector.direction.x;
	}
	if (vector.origin.y > constants.y)
	{
		vector.origin.y = constants.y;
		vector.end.y += constants.y * vector.direction.y;
	}
	draw_line(vector.origin, vector.direction, vector.distance, color);
	draw_point(vector.end, color);
}

void	coordinate_paint(int x, int y)
{
	mlx_image_t	*view;
	int			width;
	int			height;

	view = get_minimap_image();
	x = x * GRID_SIZE;
	y = y * GRID_SIZE;
	if ((uint32_t)(x + GRID_SIZE) > view->width
		|| (uint32_t)(y + GRID_SIZE) > view->height)
		return ;
	width = -1;
	while (width++ < GRID_SIZE)
	{
		height = -1;
		while (height++ < GRID_SIZE)
			mlx_put_pixel(view, x + width, y + height, HEX_WALL);
	}
}
