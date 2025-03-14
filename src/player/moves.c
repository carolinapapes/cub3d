/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_moves.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:50:40 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 05:02:22 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_vector	get_player_side(int axis, int dir)
{
	t_vector	origin;

	origin = get_player()->pos_center;
	origin.arr[axis] += PLAYER_MIDDLE * dir;
	return (origin);
}

static t_vector	get_movement_v_components(int axis, int dir)
{
	double		pov;
	t_vector	delta;

	pov = get_player()->pov;
	delta.arr[axis] = tends_to_zero(sin(pov) * dir);
	delta.arr[!axis] = tends_to_zero(cos(pov) * dir);
	if (axis == X && delta.x)
		delta.x *= -1;
	return (delta);
}

void	move(int axis, int dir)
{
	t_vector	delta;
	t_vector	quadrant;

	delta = get_movement_v_components(axis, dir);
	quadrant.x = (delta.x > 0) - (delta.x < 0);
	quadrant.y = (delta.y > 0) - (delta.y < 0);
	delta.x *= fabs(check_collition_in_axis(delta.x, X));
	delta.y *= fabs(check_collition_in_axis(delta.y, Y));
	if ((delta.x != 0 && delta.y != 0)
		|| (delta.x != 0 && quadrant.y == 0)
		|| (delta.y != 0 && quadrant.x == 0))
	{
		set_player_pos(delta);
		update_render();
		update_minimap_pos(delta);
	}
}

void	rotate(int dir)
{
	set_player_pov(dir);
	update_render();
}
