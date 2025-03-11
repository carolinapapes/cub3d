/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_moves.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:50:40 by capapes           #+#    #+#             */
/*   Updated: 2025/03/11 17:19:31 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	hits_wall(t_vector pos)
{
	pos.x /= GRID_SIZE;
	pos.y /= GRID_SIZE;
	return (get_cell_content(pos) == WALL);
}

static t_vector	get_player_side(int axis, int dir)
{
	t_vector	position;

	position = get_player_center_px();
	position.arr[axis] += PLAYER_MIDDLE * dir;
	return (position);
}

static t_vector	get_vertex(t_vector position, int axis, int dir)
{
	position.arr[!axis] += PLAYER_MIDDLE * dir;
	return (position);
}

static int	wont_intersect_grid(t_vector player_side, int axis)
{
	int	moves_left;

	moves_left = fmod(player_side.arr[axis], GRID_SIZE);
	return (moves_left > 3 && moves_left < GRID_SIZE - 3);
}

static int	vertex_check(int axis, int dir, int moves, t_vector player_side)
{
	t_vector	vertex_positive;
	t_vector	vertex_negative;

	player_side.arr[axis] += moves;
	vertex_negative = get_vertex(player_side, axis, NEGATIVE);
	vertex_positive = get_vertex(player_side, axis, POSITIVE);
	while (moves && (hits_wall(vertex_negative) || hits_wall(vertex_positive)))
	{
		moves -= dir;
		vertex_negative.arr[axis] -= dir;
		vertex_positive.arr[axis] -= dir;
	}
	return (moves);
}

int	collition_check(int axis, int dir)
{
	t_vector	player_side;
	int			moves;

	moves = 3 * dir;
	player_side = get_player_side(axis, dir);
	if (wont_intersect_grid(player_side, axis))
		return (moves);
	return (vertex_check(axis, dir, moves, player_side));
}

static inline double	tends_to_zero(double x)
{
	double	eps;

	eps = 1e-9;
	if (fabs(x) < eps)
		return (0.0);
	return (x);
}

static double	check_collition_in_axis(double delta, int axis)
{
	double	quadrant;

	quadrant = (delta > 0) - (delta < 0);
	if (delta != 0)
		delta = collition_check(axis, quadrant);
	return (delta);
}

static t_vector	get_movement_v_components(int axis, int dir)
{
	double		pov;
	t_vector	delta;

	pov = get_player().pov;
	delta.arr[axis] = tends_to_zero(sin(pov) * dir);
	delta.arr[!axis] = tends_to_zero(cos(pov) * dir);
	if (axis == X && delta.x)
		delta.x *= -1;
	return (delta);
}

void	player_move(int axis, int dir)
{
	t_vector	delta;
	t_vector	quadrant;

	delta = get_movement_v_components(axis, dir);
	quadrant = delta;
	if (quadrant.x != 0)
		delta.x = check_collition_in_axis(delta.x, X);
	if (quadrant.y != 0)
		delta.y = check_collition_in_axis(delta.y, Y);
	if (delta.x != 0 && delta.y != 0)
		set_player(delta, 0);
	else if (delta.x != 0 && quadrant.y == 0)
		set_player(delta, 0);
	else if (delta.y != 0 && quadrant.x == 0)
		set_player(delta, 0);
}

void	player_rotate(int dir)
{
	t_vector	delta;

	delta.x = 0;
	delta.y = 0;
	set_player(delta, dir);
}
