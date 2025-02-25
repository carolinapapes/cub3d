/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus_remove_later.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:21:30 by capapes           #+#    #+#             */
/*   Updated: 2025/02/25 20:23:10 by capapes          ###   ########.fr       */
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

t_vector	intersection(t_pov pov, t_vector grid, t_axis axis, t_vector origin)
{
	t_vector	next;

	if (pov.quadrant.arr[!axis] == 0)
		return (origin);
	if (axis == Y)
		pov.tan = 1 / pov.tan;
	next.arr[axis] = grid.arr[axis];
	next.arr[!axis] = origin.arr[!axis]
		+ (grid.arr[axis] - origin.arr[axis]) * pov.tan;
	return (next);
}

void	next_intersection(t_vector pos, t_vector intersect, t_player player, int axis)
{
	t_vector	next;
	t_vector	next_intersect;

	next.arr[axis] = pos.arr[!axis] + (player.pov.t_ratio.arr[!axis] * -30);
	next.arr[!axis] = pos.arr[axis] + player.pov.t_ratio.arr[axis] * 30;
	draw_point(player.mlx_view, next, HEX_PURPLE);
	next_intersect.arr[!axis] = intersect.arr[!axis] + (player.pov.t_ratio.arr[!axis] * 30);
	next_intersect.arr[axis] = intersect.arr[axis];
	draw_point(player.mlx_view, next_intersect, HEX_PURPLE);
}

double	intersect_with_wall(t_player player, int axis, uint32_t color,
	t_vector origin)
{
	t_vector	intersect;
	t_vector	grid_snap;
	t_vector	pos;
	double		len;
	int			res;

	if (player.pov.quadrant.arr[!axis] == 0)
		return (0);
	grid_snap = snap_to_grid(origin, axis, player.pov.quadrant);
	intersect = intersection(player.pov, grid_snap, axis, origin);
	len = 0;
	res = is_axis_wall(intersect, axis);
	if (res == OUTSIDE)
		return (0);
	if (res == WALL)
	{
		pos = get_player_pos(PIXEL | CENTER);
		len = hypot(intersect.x - pos.x, intersect.y - pos.y);
		draw_intersect(player, intersect, color);
		draw_axis_line(grid_snap.arr[axis], axis);
	}
	else
		len = intersect_with_wall(player, axis, color, intersect);
	return (len);
}

double	get_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
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

void update_player(t_player *player, double angle_delta)
{
	player->pov.angle += angle_delta * M_PI / 180;
	player->pov.t_ratio.x = cos(player->pov.angle);
	player->pov.t_ratio.y = sin(player->pov.angle);
	player->pov.tan = tan(player->pov.angle);
	player->pov.quadrant.x = \
		(player->pov.t_ratio.x > 0) - (player->pov.t_ratio.x < 0);
	player->pov.quadrant.y = \
		(player->pov.t_ratio.y > 0) -(player->pov.t_ratio.y < 0);
}

void	update_mlx_view(t_player player)
{
	t_vector	origin;
	double		fov;

	fov = 30;
	mlx_clear_image(player.mlx_view);
	origin = get_player_pos(CENTER_PX);
	intersect_with_wall(player, X, HEX_RED, origin);
	intersect_with_wall(player, Y, HEX_GREEN, origin);
	draw_view_plane();
	while (fov)
	{
		fov -= 5;
		update_player(&player, 5);		
		intersect_with_wall(player, X, HEX_RED, origin);
		intersect_with_wall(player, Y, HEX_GREEN, origin);
	}
}
