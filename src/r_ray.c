/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:21:30 by capapes           #+#    #+#             */
/*   Updated: 2025/03/07 15:57:19 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static t_vector_full	init_ray(t_vector origin, double angle)
{
	t_vector_full	ray;

	ray.direction.x = cos(angle);
	ray.direction.y = sin(angle);
	ray.tan.x = tan(angle);
	ray.tan.y = 1 / ray.tan.x;
	ray.quadrant.x = \
		(ray.direction.x > 0) - (ray.direction.x < 0);
	ray.quadrant.y = \
		(ray.direction.y > 0) - (ray.direction.y < 0);
	ray.origin = origin;
	ray.end = origin;
	ray.distance = 0;
	return (ray);
}

t_vector_full	get_ray(t_vector_full ray)
{
	t_vector_full	ray_x;
	t_vector_full	ray_y;

	ray_x = get_ray_intersection(ray, X);
	ray_y = get_ray_intersection(ray, Y);
	if (ray_x.distance && (ray_x.distance <= ray_y.distance || !ray_y.distance))
	{
		ray_x.axis = X;
		return (ray_x);
	}
	ray_y.axis = Y;
	return (ray_y);
}

void	draw_ray(t_vector_full ray, double angle, double iter)
{
	if (!ray.distance)
		return ;
	draw_intersect(ray, HEX_GREY - 0x20202020);
	if (angle != 0)
		ray.distance *= cos(angle);
	set_ongoing_view_wall(ray.end.arr[ray.axis], ray.quadrant.arr[!ray.axis]);
	set_texture_x(ray.end.arr[!ray.axis]);
	draw_render(ray.distance, iter);
}

/*
* @brief: Iterates over the field of view and draws the rays
* @param: origin: the player position
* @param: pov: the player point of view
*/
void	pov_iter(t_vector origin, double pov)
{
	double			angle;
	double			iter;
	t_constants		constants;
	t_vector_full	ray;

	iter = -1;
	constants = game_constants();
	angle = pov + constants.fov_delta_start;
	mlx_clear_image(get_miniview_image());
	mlx_clear_image(get_render_image());
	mlx_clear_image(get_shadow_image());
	while (iter++ < WIDTH)
	{
		angle += constants.angle_step;
		ray = init_ray(origin, angle);
		ray = get_ray(ray);
		draw_ray(ray, angle - pov, iter);
	}
}
