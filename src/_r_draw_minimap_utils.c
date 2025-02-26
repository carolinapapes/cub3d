/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _r_draw_minimap_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:18:39 by capapes           #+#    #+#             */
/*   Updated: 2025/02/26 15:19:25 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_intersect(t_vector_full vector, int color)
{
	draw_line(vector.origin, vector.direction, vector.distance, color);
	draw_point(vector.end, color);
}

void	draw_view_plane(void)
{
	t_player	player;
	t_vector	inverse;
	t_vector	origin;

	player = get_player();
	origin = get_player_pos(PIXEL | CENTER);
	inverse.x = -player.pov.t_ratio.y;
	inverse.y = player.pov.t_ratio.x;
	while (origin.x >= 0 && origin.x < WIDTH && origin.y >= 0
		&& origin.y < HEIGHT)
	{
		draw_pixel(player.mlx_view, origin, HEX_BLUE);
		origin.x += inverse.x;
		origin.y += inverse.y;
	}
	origin = get_player_pos(PIXEL | CENTER);
	while (origin.x >= 0 && origin.x < WIDTH && origin.y >= 0
		&& origin.y < HEIGHT)
	{
		draw_pixel(player.mlx_view, origin, HEX_BLUE);
		origin.x -= inverse.x;
		origin.y -= inverse.y;
	}
}
