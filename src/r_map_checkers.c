/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_map_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:26:00 by capapes           #+#    #+#             */
/*   Updated: 2025/03/01 11:37:43 by capapes          ###   ########.fr       */
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

int	is_axis_wall(t_vector cell, t_axis axis, t_vector_full ray)
{
	cell.x = cell.x / GRID_SIZE;
	cell.y = cell.y / GRID_SIZE;
	if (ray.quadrant.arr[axis] == 1)
	{
		cell.arr[axis]--;
		if (get_cell_content(cell) == WALL)
			return (WALL);
		cell.arr[axis]++;
		return (get_cell_content(cell));
	}
	if (get_cell_content(cell) == WALL)
		return (WALL);
	cell.arr[axis]--;
	return (get_cell_content(cell));
}
