/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collitions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 04:57:08 by capapes           #+#    #+#             */
/*   Updated: 2025/03/17 15:57:03 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	hits_wall(t_vector pos, double move, int axis)
{
	pos.arr[axis] += move;
	return (get_cell_content(pos) == WALL);
}

static t_vector	get_vertex(t_vector position, int axis, int dir)
{
	position.arr[!axis] += PLAYER_MIDDLE * dir;
	position.arr[!axis] /= (double) GRID_SIZE;
	position.arr[axis] /= (double) GRID_SIZE;
	return (position);
}

static int	check_grid_collision(t_vector player_side, int axis)
{
	int	moves_left;

	moves_left = fmod(player_side.arr[axis], GRID_SIZE);
	return (moves_left > 3 && moves_left < GRID_SIZE - 3);
}

static int	vertex_check(int axis, int dir, int moves, t_vector player_side)
{
	t_vector	vertex_positive;
	t_vector	vertex_negative;
	double		move_grid;
	double		px_move;

	px_move = 1.00 / GRID_SIZE * dir;
	move_grid = (double)moves / GRID_SIZE;
	vertex_negative = get_vertex(player_side, axis, NEGATIVE);
	vertex_positive = get_vertex(player_side, axis, POSITIVE);
	while (move_grid
		&& (hits_wall(vertex_negative, move_grid, axis)
			|| hits_wall(vertex_positive, move_grid, axis)))
		move_grid -= px_move;
	return (move_grid * GRID_SIZE);
}

double	check_collition_in_axis(double delta, int axis)
{
	double		dir;
	t_vector	player_side;
	int			moves;

	if (delta == 0)
		return (0);
	dir = (delta > 0) - (delta < 0);
	moves = 3 * dir;
	player_side = get_player_side(axis, dir);
	if (check_grid_collision(player_side, axis))
		return (moves);
	return (vertex_check(axis, dir, moves, player_side));
}
