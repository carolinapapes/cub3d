/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ray_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:40:59 by capapes           #+#    #+#             */
/*   Updated: 2025/03/04 15:54:35 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static double	snap_to_grid(double origin, int quadrant)
{
	origin = origin / GRID_SIZE;
	if ((int)origin == origin)
		origin += quadrant;
	else
		origin = (int)origin + (quadrant == POSITIVE);
	origin = origin * GRID_SIZE;
	return (origin);
}

t_vector	next_grid(t_vector_full ray, t_axis axis)
{
	t_vector	next;

	next.arr[axis] = snap_to_grid(ray.end.arr[axis], ray.quadrant.arr[axis]);
	next.arr[!axis] = ray.end.arr[!axis]
		+ get_side_len(next, ray.end, ray.tan, axis);
	return (next);
}

t_vector_full	get_ray_intersection(t_vector_full ray, int axis)
{
	int				type;

	if (ray.quadrant.arr[!axis] == 0)
		return (ray);
	ray.end = next_grid(ray, axis);
	type = is_axis_wall(ray.end, axis, ray);
	if (type == OUTSIDE)
		return (ray);
	if (type != WALL)
		return (get_ray_intersection(ray, axis));
	ray.distance = get_hypot(ray.origin, ray.end);
	return (ray);
}
