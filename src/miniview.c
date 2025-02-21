/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:53:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/21 19:20:12 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static double	get_axis_grid_distance(t_player player, t_axis axis)
{
	double	pos;
	int		quadrant;

	pos = get_player_pos(PLAYER_PIXEL_CENTER).arr[axis];
	quadrant = player.pov.quadrant.arr[axis];
	if (quadrant == POSITIVE)
		return (ceil((pos + PLAYER_MIDDLE) / GRID_SIZE) * GRID_SIZE);
	if (quadrant == NEGATIVE)
		return (floor((pos - PLAYER_MIDDLE) / GRID_SIZE) * GRID_SIZE);
	return (player.pos.arr[axis] + PLAYER_MIDDLE);
}

t_vector	get_grid_distance(t_player player)
{
	t_vector	grid_distance;

	grid_distance.x = get_axis_grid_distance(player, X);
	grid_distance.y = get_axis_grid_distance(player, Y);
	return (grid_distance);
}
