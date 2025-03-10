/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_moves.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:50:40 by capapes           #+#    #+#             */
/*   Updated: 2025/03/10 12:30:34 by capapes          ###   ########.fr       */
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
// t_vector	compute_delta(int key)
// {
// 	double		pov;
// 	t_vector	delta;

// 	pov = get_player().pov;
// 	delta.x = 0;
// 	delta.y = 0;
// 	if (key == MLX_KEY_W) // axis y - dir +
// 	{
// 		delta.x = cos(pov);
// 		delta.y = sin(pov);
// 	}
// 	if (key == MLX_KEY_S) // axis y - dir -
// 	{
// 		delta.x = -cos(pov);
// 		delta.y = -sin(pov);
// 	}
// 	if (key == MLX_KEY_A) // axis x - dir -
// 	{
// 		delta.x = sin(pov);
// 		delta.y = -cos(pov);
// 	}
// 	if (key == MLX_KEY_D) // axis x - dir +
// 	{
// 		delta.x = -sin(pov);
// 		delta.y = cos(pov);
// 	}
// 	return (delta);
// }

	// delta.arr[!axis] = 0;
	// delta.arr[axis] = collition_check(axis, dir);
	// delta = compute_delta(key);
	// if (delta.arr[axis] != 0)
void	player_move(int axis, int dir)
{
	t_vector	delta;
	double		pov;
	t_vector	quadrant;

	pov = get_player().pov;
	delta.arr[axis] = sin(pov) * dir;
	delta.arr[!axis] = cos(pov) * dir;
	if (axis == X)
		delta.x *= -1;
	quadrant.x = (delta.x > 0) - (delta.x < 0);
	quadrant.y = (delta.y > 0) - (delta.y < 0);
	delta.arr[axis] = collition_check(axis, quadrant.arr[axis]);
	delta.arr[!axis] = collition_check(!axis, quadrant.arr[!axis]);
	if ((delta.x != 0 && delta.y != 0)
		|| (delta.x != 0 && !quadrant.y)
		|| (delta.y != 0 && !quadrant.x))
		set_player(delta, 0);
}

void	player_rotate(int dir)
{
	t_vector	delta;

	delta.x = 0;
	delta.y = 0;
	set_player(delta, dir);
}
