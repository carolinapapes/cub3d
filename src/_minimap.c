/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minimap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:00:50 by capapes           #+#    #+#             */
/*   Updated: 2025/03/13 19:48:12 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_mlx_miniplayer_pos(t_vector position, int axis)
{
	mlx_image_t	*mlx_player;

	mlx_player = get_miniplayer();
	if (axis == Y)
		mlx_player->instances[0].y = position.y;
	if (axis == X)
		mlx_player->instances[0].x = position.x;
}

void	update_mlx_minimap_position(t_vector pos_delta, int axis)
{
	mlx_image_t	*mlx_aux;

	mlx_aux = get_minimap();
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

void	update_minimap_pos(t_vector delta)
{
	t_vector	constants;
	t_vector	position;

	constants = game_constants().limit_movement;
	position = get_player()->pos;
	update_minimap_axis(constants, position, delta, X);
	update_minimap_axis(constants, position, delta, Y);
}
