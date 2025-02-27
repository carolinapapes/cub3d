/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus_remove_later.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:21:30 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 11:18:12 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_vector	next_grid(t_vector_full ray, t_axis axis)
{
	t_vector	next;

	next.arr[axis] = snap_to_grid(ray.end.arr[axis], ray.quadrant.arr[axis]);
	next.arr[!axis] = ray.end.arr[!axis]
		+ (next.arr[axis] - ray.end.arr[axis]) * ray.tan.arr[axis];
	return (next);
}

t_vector_full	intersect(t_vector_full ray, int axis)
{
	int				type;

	if (ray.quadrant.arr[!axis] == 0)
		return (ray);
	ray.end = next_grid(ray, axis);
	type = is_axis_wall(ray.end, axis);
	if (type == OUTSIDE)
		return (ray);
	if (type == GRID)
		return (intersect(ray, axis));
	ray.distance = hypot(ray.end.x - ray.origin.x, ray.end.y - ray.origin.y);
	return (ray);
}

void	draw_rendered_view(double wall_distance, u_int32_t color, int iter)
{
	int				wall_strip_height;
	int				start;
	int				end;
	t_vector		wall_start;
	t_constants		constants;

	start = iter * constants.wall_strip_width;
	end = start + constants.wall_strip_width;
	wall_strip_height = constants.wall_strip_height / wall_distance;
	wall_start.y = (HEIGHT - wall_strip_height) / 2;
	while (start < end && start < WIDTH)
	{
		wall_start.x = start;
		draw_line_render(wall_start, constants.dir_y, wall_strip_height, color);
		start++;
	}
}

t_vector_full	update_ray(t_vector origin, double angle)
{
	t_vector_full	ray;

	ray.direction.x = cos(angle);
	ray.direction.y = sin(angle);
	ray.tan.x = tan(angle);
	ray.tan.y = 1 / ray.tan.x;
	ray.quadrant.x = \
		(ray.direction.x > 0) - (ray.direction.x < 0);
	ray.quadrant.y = \
		(ray.direction.y > 0) -(ray.direction.y < 0);
	ray.origin = origin;
	ray.end = origin;
	ray.distance = 0;
	return (ray);
}

void	draw_render_inter(t_vector_full ray, int iter)
{
	t_vector_full	ray_x;
	t_vector_full	ray_y;

	ray_x = intersect(ray, X);
	ray_y = intersect(ray, Y);
	if (ray_x.distance != 0
		&& (ray_x.distance <= ray_y.distance || ray_y.distance == 0))
	{
		draw_intersect(ray_x, HEX_GREY);
		draw_rendered_view(ray_x.distance, HEX_GREEN - 0x00000066, iter);
	}
	else if (ray_y.distance != 0)
	{
		draw_rendered_view(ray_y.distance, HEX_RED - 0x00000066, iter);
		draw_intersect(ray_y, HEX_GREY);
	}
}

void	pov_iter(t_vector origin, double angle_fov)
{
	double			angle;
	double			iter;
	t_constants		constants;
	t_vector_full	ray;

	iter = 0;
	angle = angle.fov - constants.fov_delta_start;
	while (iter++ < 61)
	{
		angle += constants.angle_step;
		ray = update_ray(origin, angle);
		draw_render_inter(ray, iter);
	}
}

void	update_mlx_view(t_player player)
{
	t_vector		origin;

	origin = get_player_pos(PIXEL | CENTER);
	mlx_clear_image(player.mlx_view);
	mlx_clear_image(get_aux());
	mlx_clear_image(get_render());
	pov_iter(origin, player.pov.angle);
}
