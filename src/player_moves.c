/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:50:40 by capapes           #+#    #+#             */
/*   Updated: 2025/02/20 18:54:39 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	hits_wall(t_vector pos, int axis)
{
	if (is_fixed_object(pos.x, pos.y) & WALL)
		return (1);
	pos.arr[!axis] += PLAYER_SIZE - 1;
	if (is_fixed_object(pos.x, pos.y) & WALL)
		return (1);
	return (0);
}

t_vector	collition_check(int axis, int dir)
{
	t_vector	moves;
	t_vector	position;

	if (dir == POSITIVE)
		position.arr[axis] += ((PLAYER_SIZE - 1) * dir);
	position = get_player_pos();
	moves.arr[axis] = 3 * dir;
	position.arr[axis] += moves.arr[axis];
	while (moves.arr[axis] && hits_wall(position, axis))
	{
		moves.arr[axis] -= dir;
		position.arr[axis] -= dir;
	}
	return (moves);
}

void	player_hook(t_axis axis, int dir)
{
	t_vector	delta;

	delta.x = 0;
	delta.y = 0;
	if (axis == X)
		delta.x = dir;
	else if (axis == Y)
		delta.y = dir;
	set_player(delta);
}
