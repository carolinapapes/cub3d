/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus_remove_later.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:21:30 by capapes           #+#    #+#             */
/*   Updated: 2025/02/26 13:23:49 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*init_player_image(void)
{
	t_vector	size;
	t_vector	origin;
	mlx_image_t	*image;

	origin.x = 0;
	origin.y = 0;
	size.x = PLAYER_SIZE;
	size.y = PLAYER_SIZE;
	image = new_image(size, origin);
	image_full_color(image, PLAYER_COLOR);
	return (image);
}

mlx_image_t	*get_view(void)
{
	static mlx_image_t	*mlx_view;

	if (!mlx_view)
		mlx_view = new_image_full();
	return (mlx_view);
}

void	update_mlx_player(t_player *player)
{
	player->mlx_player->instances[0].x = player->pos.x;
	player->mlx_player->instances[0].y = player->pos.y;
}

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

void	draw_view_plane(void)
{
	t_player	player;
	t_vector	inverse;
	t_vector	origin;

	player = get_player();
	origin = get_player_pos(PIXEL | CENTER);
	inverse.x = -player.pov.t_ratio.y;
	inverse.y = player.pov.t_ratio.x;
	while (origin.x >= 0 && origin.x < WIDTH && origin.y >= 0
		&& origin.y < HEIGHT)
	{
		draw_pixel(player.mlx_view, origin, HEX_BLUE);
		origin.x += inverse.x;
		origin.y += inverse.y;
	}
	origin = get_player_pos(PIXEL | CENTER);
	while (origin.x >= 0 && origin.x < WIDTH && origin.y >= 0
		&& origin.y < HEIGHT)
	{
		draw_pixel(player.mlx_view, origin, HEX_BLUE);
		origin.x -= inverse.x;
		origin.y -= inverse.y;
	}
}

void	update_mlx_view(t_player player)
{
	t_vector_full	ray;

	mlx_clear_image(player.mlx_view);
	mlx_clear_image(get_aux());
	ray.distance = 0;
	ray.direction = player.pov.t_ratio;
	ray.origin = get_player_pos(PIXEL | CENTER);
	ray.end = ray.origin;
	ray.quadrant = player.pov.quadrant;
	ray.tan = player.pov.tan;
	ray = intersect(ray, X);
	if (ray.distance != 0)
		draw_intersect_2(ray, HEX_RED);
	ray.end = ray.origin;
	ray = intersect(ray, Y);
	if (ray.distance != 0)
		draw_intersect_2(ray, HEX_GREEN);
	draw_view_plane();
}

// void update_player(t_player *player, double angle_delta)
// {
// 	player->pov.angle += angle_delta * M_PI / 180;
// 	player->pov.t_ratio.x = cos(player->pov.angle);
// 	player->pov.t_ratio.y = sin(player->pov.angle);
// 	player->pov.tan = tan(player->pov.angle);
// 	player->pov.quadrant.x = \
// 		(player->pov.t_ratio.x > 0) - (player->pov.t_ratio.x < 0);
// 	player->pov.quadrant.y = \
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
