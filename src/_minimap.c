/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minimap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:50 by capapes           #+#    #+#             */
/*   Updated: 2025/03/11 18:41:15 by capapes          ###   ########.fr       */
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
		mlx_player->instances[0].y = position.y;
	if (axis == X)
		mlx_player->instances[0].x = position.x;
}

void	update_mlx_minimap_position(t_vector pos_delta, int axis)
{
	mlx_image_t	*mlx_aux;

	mlx_aux = get_minimap_image();
	if (axis == Y)
		mlx_aux->instances[0].y -= pos_delta.y;
	if (axis == X)
		mlx_aux->instances[0].x -= pos_delta.x;
}

void	update_minimap_axis(t_vector constants, t_vector position,
	t_vector position_delta, int axis)
{
	if (position.arr[axis] <= constants.arr[axis])
		update_mlx_miniplayer_pos(position, axis);
	else
		update_mlx_minimap_position(position_delta, axis);
}

void	update_minimap_pos(t_vector position, t_vector position_delta)
{
	t_vector	constants;

	constants = game_constants().limit_movement;
	update_minimap_axis(constants, position, position_delta, X);
	update_minimap_axis(constants, position, position_delta, Y);
}
