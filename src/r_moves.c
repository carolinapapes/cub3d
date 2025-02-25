/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_moves.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:50:40 by capapes           #+#    #+#             */
/*   Updated: 2025/02/25 12:28:35 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	hits_wall(t_vector pos, int axis)
{
	pos.arr[!axis] -= PLAYER_SIZE / 2;
	if (is_fixed_object(pos.x, pos.y) & WALL)
		return (1);
	pos.arr[!axis] += PLAYER_SIZE - 1;
	if (is_fixed_object(pos.x, pos.y) & WALL)
		return (1);
	return (0);
}

int	collition_check(int axis, int dir)
{
	int			moves;
	t_vector	position;

	moves = 3 * dir;
	position = get_player_pos(CENTER_PX);
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
