/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collitions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:29:39 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 04:23:32 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define MOVES 3
#define NO_MOVES -2
#define ALL_MOVES -1

int	vertex_check(int axis, double moves, t_vector side, int dir)
{
	t_vector	vertex;

	vertex.arr[axis] = (side.arr[axis] + moves * dir) / GRID_SIZE;
	vertex.arr[!axis] = (side.arr[!axis] - PLAYER_MIDDLE) / GRID_SIZE;
	if (get_cell_content(vertex) == WALL)
		return (moves);
	vertex.arr[!axis] = (side.arr[!axis] + PLAYER_MIDDLE) / GRID_SIZE;
	if (get_cell_content(vertex) == WALL)
		return (moves);
	return (MOVES);
}

static int	get_moves_to_grid(t_vector player_side, int axis)
{
	int	moves;

	moves = fmod(player_side.arr[axis], GRID_SIZE);
	if (moves <= MOVES)
		return (moves);
	if (moves >= GRID_SIZE - MOVES)
		return (GRID_SIZE - moves);
	return (ALL_MOVES);
}

static t_vector	get_player_side(int axis, int dir)
{
	t_vector	origin;

	origin = get_player()->pos_center;
	origin.arr[axis] += PLAYER_MIDDLE * dir;
	return (origin);
}

int	get_moves_quantity(int axis, double dir)
{
	t_vector	player_side;
	int			moves;

	player_side = get_player_side(axis, dir);
	moves = get_moves_to_grid(player_side, axis);
	if (moves == ALL_MOVES)
		return (MOVES);
	moves = vertex_check(axis, moves, player_side, dir);
	return (moves);
}

double	get_available_moves(double delta, int axis)
{
	double		dir;
	double		available;

	if (delta == 0)
		return (0);
	dir = (delta > 0) - (delta < 0);
	available = get_moves_quantity(axis, dir);
	return (available);
}
