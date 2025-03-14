/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collitions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 04:57:08 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 13:15:17 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	hits_wall(t_vector pos)
{
	pos.x /= GRID_SIZE;
	pos.y /= GRID_SIZE;
	return (get_cell_content(pos) == WALL);
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

double	check_collition_in_axis(double delta, int axis)
{
	double		quadrant;
	t_vector	player_side;
	int			moves;

	quadrant = (delta > 0) - (delta < 0);
	if (delta == 0)
		return (0);
	moves = 3 * quadrant;
	player_side = get_player_side(axis, quadrant);
	if (wont_intersect_grid(player_side, axis))
		return (moves);
	return (vertex_check(axis, quadrant, moves, player_side));
}
