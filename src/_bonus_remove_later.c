/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus_remove_later.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:21:30 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 18:02:31 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_render(double distance, uint32_t color, int iter)
{
	int				strip_height;
	int				end;
	t_vector		wall_start;
	t_constants		constants;

	constants = game_constants();
	wall_start.x = (iter - 1) * constants.strip_width;
	end = wall_start.x + constants.strip_width;
	strip_height = constants.strip_height / distance;
	wall_start.y = (HEIGHT - strip_height) / 2;
	while (wall_start.x++ < end && wall_start.x < WIDTH)
		draw_line_render(wall_start, constants.dir_y, strip_height, color);
}

static t_vector_full	update_ray(t_vector origin, double angle)
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

static void	draw_render_inter(t_vector_full ray, int iter)
{
	t_vector_full	ray_x;
	t_vector_full	ray_y;

	ray_x = intersect(ray, X);
	ray_y = intersect(ray, Y);
	if (ray_x.distance != 0
		&& (ray_x.distance <= ray_y.distance || ray_y.distance == 0))
	{
		draw_intersect(ray_x, HEX_GREY);
		draw_render(ray_x.distance, HEX_GREEN - 0x00000066, iter);
	}
	else if (ray_y.distance != 0)
	{
		draw_render(ray_y.distance, HEX_RED - 0x00000066, iter);
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
	constants = game_constants();
	angle = angle_fov - constants.fov_delta_start;
	while (iter++ < 61)
	{
		angle += constants.angle_step;
		ray = update_ray(origin, angle);
		draw_render_inter(ray, iter);
	}
}
