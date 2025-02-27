/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _r_draw_minimap_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:18:39 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 18:18:06 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_intersect(t_vector_full vector, int color)
{
	draw_line(vector.origin, vector.direction, vector.distance, color);
	draw_point(vector.end, color);
}

// void	draw_view_plane(t_vector_full ray)
// {
// 	t_vector	inverse;
// 	t_vector	origin;
// 	mlx_image_t	*mlx_view;

// 	mlx_view = get_view_image();
// 	origin = get_player_pos(PIXEL | CENTER);
// 	inverse.x = -ray.direction.y;
// 	inverse.y = ray.direction.x;
// 	while (origin.x >= 0 && origin.x < WIDTH && origin.y >= 0
// 		&& origin.y < HEIGHT)
// 	{
// 		// draw_pixel(mlx_view, origin, HEX_BLUE);
// 		origin.x += inverse.x;
// 		origin.y += inverse.y;
// 	}
// 	origin = get_player_pos(PIXEL | CENTER);
// 	while (origin.x >= 0 && origin.x < WIDTH && origin.y >= 0
// 		&& origin.y < HEIGHT)
// 	{
// 		// draw_pixel(mlx_view, origin, HEX_BLUE);
// 		origin.x -= inverse.x;
// 		origin.y -= inverse.y;
// 	}
// }

void	coordinate_paint(int x, int y)
{
	mlx_image_t	*view;
	int			width;
	int			height;

	view = get_view_image();
	x *= GRID_SIZE;
	y *= GRID_SIZE;
	width = 0;
	while (width < GRID_SIZE)
	{
		height = 0;
		while (height < GRID_SIZE)
		{
			if (x + width > WIDTH || y + height > HEIGHT)
				return ;
			mlx_put_pixel(view, x + width, y + height,
				HEX_PURPLE - width * 0x00000100 - height * 0x00010000);
			height++;
		}
		width++;
	}
}
