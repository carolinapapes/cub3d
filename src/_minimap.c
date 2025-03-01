/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minimap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:50 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 23:03:14 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"



void	draw_minimap(t_vector coord)
{
	int			content;
	mlx_image_t	*image;

	image = get_minimap_image();
	content = get_cell_content(coord);
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

void	update_minimap_pos(t_vector position, t_vector position_delta)
{
	mlx_image_t	*image;
	t_vector	constants;

	image = get_minimap_image();
	constants = game_constants().limit_movement;
	if (position.x <= constants.x)
		update_mlx_miniplayer_pos(position_delta, X);
	else
		image->instances[0].x -= position_delta.x;
	if (position.y <= constants.y)
		update_mlx_miniplayer_pos(position_delta, Y);
	else
		image->instances[0].y -= position_delta.y;
}
