/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:50:40 by capapes           #+#    #+#             */
/*   Updated: 2025/03/17 16:07:42 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

t_vector	get_player_side(int axis, int dir)
{
	t_vector	origin;

	origin = get_player()->pos_center;
	origin.arr[axis] += PLAYER_MIDDLE * dir;
	return (origin);
}

static t_vector	get_move_components(int axis, int dir)
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

double	get_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

void	move(int axis, int dir)
{
	t_vector	delta;
	t_vector	available_moves;

	delta = get_move_components(axis, dir);
	available_moves.x = fabs(check_collition_in_axis(delta.x, X));
	available_moves.y = fabs(check_collition_in_axis(delta.y, Y));
	if (available_moves.x == 0 && available_moves.y == 0)
		return ;
	if (available_moves.x != 0 && available_moves.y != 0)
	{
		available_moves.x = get_min(available_moves.x, available_moves.y);
		available_moves.y = available_moves.x;
	}
	delta.x *= available_moves.x;
	delta.y *= available_moves.y;
	set_player_pos(delta);
	set_render();
	set_minimap_pos(delta);
}

void	rotate(int dir)
{
	set_player_pov(dir);
	set_render();
}
