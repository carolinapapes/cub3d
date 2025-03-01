/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_moves.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:50:40 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 23:03:14 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	hits_wall(t_vector pos, int axis)
{
	t_vector	position_coord;

	pos.arr[!axis] += PLAYER_MIDDLE;
	position_coord.x = pos.x / GRID_SIZE;
	position_coord.y = pos.y / GRID_SIZE;
	if (get_cell_content(position_coord) == WALL)
		return (1);
	pos.arr[!axis] -= PLAYER_SIZE - 1;
	position_coord.arr[!axis] = pos.arr[!axis] / GRID_SIZE;
	if (get_cell_content(position_coord) == WALL)
		return (1);
	return (0);
}

static int	collition_check(int axis, int dir)
{
	int			moves;
	t_vector	position;

	moves = 3 * dir;
	position = get_player_center_px();
	position.arr[axis] += PLAYER_MIDDLE * dir;
	position.arr[axis] += moves;
	while (moves && hits_wall(position, axis))
	{
		moves -= dir;
		position.arr[axis] -= dir;
	}
	return (moves);
}

void	player_move(t_axis axis, int dir)
{
	t_vector	delta;

	delta.arr[!axis] = 0;
	delta.arr[axis] = collition_check(axis, dir);
	if (delta.arr[axis] != 0)
		set_player(delta, 0);
}

void	player_rotate(int dir)
{
	t_vector	delta;

	delta.x = 0;
	delta.y = 0;
	set_player(delta, dir);
}
