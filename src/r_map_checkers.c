/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_map_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:26:00 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 23:12:41 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_cell_content(t_vector coord)
{
	int			content;
	t_start		*start;

	start = get_start();
	if (coord.x < 0 || coord.y < 0
		|| coord.x >= start->map.size_int.x || coord.y >= start->map.size_int.y)
		return (OUTSIDE);
	content = start->map.map_int[(int)coord.y][(int)coord.x];
	return (content);
}

int	is_axis_wall(t_vector axis_positive, t_axis axis, t_vector_full ray)
{
	t_vector	axis_negative;

	axis_positive.x = axis_positive.x / GRID_SIZE;
	axis_positive.y = axis_positive.y / GRID_SIZE;
	axis_negative = axis_positive;
	axis_negative.arr[axis] = axis_negative.arr[axis] - 1;
	if (ray.quadrant.arr[axis] == 1 && get_cell_content(axis_negative) == WALL)
		return (WALL);
	if (ray.quadrant.arr[axis] == -1 && get_cell_content(axis_positive) == WALL)
		return (WALL);
	if (ray.quadrant.arr[!axis] == 1)
		return (get_cell_content(axis_positive));
	return (get_cell_content(axis_negative));
}
