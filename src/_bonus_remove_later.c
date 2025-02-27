/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus_remove_later.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:21:30 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 10:25:40 by capapes          ###   ########.fr       */
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

t_vector_full	get_ray(t_player player)
{
	t_vector_full	ray;

	ray.distance = 0;
	ray.direction = player.pov.t_ratio;
	ray.origin = get_player_pos(PIXEL | CENTER);
	ray.end = ray.origin;
	ray.quadrant = player.pov.quadrant;
	ray.tan = player.pov.tan;
	return (ray);
}

void	draw_rendered_view(double wall_distance, u_int32_t color, int iter)
{
	int				wall_strip_height;
	int				wall_strip_width;
	int				start;
	int				end;
	t_vector		wall_start;
	t_vector		direction;

	wall_strip_width = WIDTH / 60;
	start = iter * wall_strip_width;
	end = (iter + 1) * wall_strip_width;
	wall_strip_height = (HEIGHT * 150) / wall_distance;
	wall_start.y = HEIGHT / 2 - wall_strip_height / 2;
	direction.y = 1;
	direction.x = 0;
	while (start < end && start < WIDTH)
	{
		wall_start.x = start;
		draw_line_render(wall_start, direction, wall_strip_height, color);
		start++;
	}
}

t_vector_full	update_ray(t_vector_full ray, double angle)
{
	ray.direction.x = cos(angle);
	ray.direction.y = sin(angle);
	ray.tan.x = tan(angle);
	ray.tan.y = 1 / ray.tan.x;
	ray.quadrant.x = \
		(ray.direction.x > 0) - (ray.direction.x < 0);
	ray.quadrant.y = \
		(ray.direction.y > 0) -(ray.direction.y < 0);
	ray.end = ray.origin;
	ray.distance = 0;
	return (ray);
}

void	update_mlx_view(t_player player)
{
	t_vector_full	ray_x;
	t_vector_full	ray_y;
	t_vector_full	ray;
	double			angle;
	double			iter;

	ray = get_ray(player);
	mlx_clear_image(player.mlx_view);
	mlx_clear_image(get_aux());
	mlx_clear_image(get_render());
	iter = 0;
	angle = player.pov.angle;
	while (iter < 60)
	{
		angle = player.pov.angle + (iter - 30) * M_PI / 180;
		ray = update_ray(ray, angle);
		ray_x = intersect(ray, X);
		ray_y = intersect(ray, Y);
		if (ray_x.distance != 0 && (ray_x.distance <= ray_y.distance || ray_y.distance == 0))
		{
			draw_intersect(ray_x, HEX_GREY);
			draw_rendered_view(ray_x.distance, HEX_GREEN - 0x00000066, iter);
		}
		else if (ray_y.distance != 0 && (ray_y.distance < ray_x.distance || ray_x.distance == 0))
		{
			draw_rendered_view(ray_y.distance, HEX_RED - 0x00000066, iter);
			draw_intersect(ray_y, HEX_GREY);
		}
		iter++;
	}
	// draw_view_plane();
}

// void update_player(t_player *player, double angle_delta)
// {
// 	player->pov.angle += angle_delta * M_PI / 180;
// 	player->pov.t_ratio.x = cos(player->pov.angle);
// 	player->pov.t_ratio.y = sin(player->pov.angle);
// 	player->pov.tan = tan(player->pov.angle);
// 	player->pov.quadrant.x = 
// 		(player->pov.t_ratio.x > 0) - (player->pov.t_ratio.x < 0);
// 	player->pov.quadrant.y = 
// 		(player->pov.t_ratio.y > 0) -(player->pov.t_ratio.y < 0);
// }

// update_player(&player, 30);
// intersect_with_wall(player, X, HEX_RED, origin);
// intersect_with_wall(player, Y, HEX_GREEN, origin);
// update_player(&player, -60);
// intersect_with_wall(player, X, HEX_RED, origin);
// intersect_with_wall(player, Y, HEX_GREEN, origin);

// // Calculate the determinant (Delta)
// // If determinant is zero, the lines are parallel (no intersection)
// void	draw_next_grid_intersections(t_vector quadrant,
// 		t_vector intersect, int axis, u_int32_t color)
// {
// 	t_vector	grid_snap;
// 	t_vector	inverse;
// 	t_vector	dir;
// 	int			original_len;
// 	int			len;
// 	t_vector	pos;

// 	dir = get_player().pov.t_ratio;
// 	pos = get_player_pos(PIXEL | CENTER);
// 	grid_snap = snap_to_grid(intersect, !axis, quadrant);
// 	draw_point(grid_snap, color - 0x00000088);
// 	inverse.x = -dir.y;
// 	inverse.y = dir.x;
// 	draw_line(grid_snap, inverse, 100, HEX_GREEN - 0x00000088);
// 	inverse.x = -inverse.x;
// 	inverse.y = -inverse.y;
// 	draw_line(grid_snap, inverse, 100, HEX_GREEN - 0x00000088);
// 	inverse.x = -dir.x;
// 	inverse.y = -dir.y;
// 	original_len = hypot(intersect.x - pos.x, intersect.y - pos.y);
// 	len = intersect.arr[!axis] - grid_snap.arr[!axis];
// 	len = get_player().pov.tan * len;
// 	printf("len: %d\n", len);
// 	draw_line(grid_snap, inverse, abs(original_len + len), HEX_GREEN);
// 	quadrant.arr[!axis] = (quadrant.arr[!axis] < 0) - (quadrant.arr[!axis] > 0);
// 	grid_snap = snap_to_grid(intersect, !axis, quadrant);
// 	draw_point(grid_snap, color - 0x00000088);
// 	inverse.x = -dir.y;
// 	inverse.y = dir.x;
// 	draw_line(grid_snap, inverse, 100, HEX_GREEN - 0x00000088);
// 	inverse.x = -inverse.x;
// 	inverse.y = -inverse.y;
// 	draw_line(grid_snap, inverse, 100, HEX_GREEN - 0x00000088);
// 	inverse.x = -dir.x;
// 	inverse.y = -dir.y;
// 	original_len = fabs(hypot(intersect.x - pos.x, intersect.y - pos.y));
// 	len = fabs(intersect.arr[!axis] - grid_snap.arr[!axis]);
// 	len = fabs(get_player().pov.tan * len);
// 	printf("len: %d\n", len);
// 	draw_line(grid_snap, inverse, original_len - len, HEX_GREEN);
// }
