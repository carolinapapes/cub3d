/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus_remove_later.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:21:30 by capapes           #+#    #+#             */
/*   Updated: 2025/02/23 17:02:47 by capapes          ###   ########.fr       */
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

void	draw_intersect(t_player player, t_vector pos, t_vector point, int len, int color)
{
	draw_line(player.mlx_view, pos, player.pov.t_ratio, len, color);
	draw_point(player.mlx_view, point, color);
}

void	next_intersection_x(t_vector prev, t_player player)
{
	t_vector	next;
	int			len;

	next.x = prev.x + GRID_SIZE * player.pov.quadrant.x;
	if (player.pov.quadrant.y == 0)
		next.y = prev.y;
	else
		next.y = prev.y + GRID_SIZE * tan(player.pov.angle) * player.pov.quadrant.x;
	len = (int)hypot(next.x - prev.x, next.y - prev.y);
	draw_intersect(player, prev, next, len, HEX_RED - 0x00000088);
	draw_point(player.mlx_view, next, HEX_RED - 0x00000088);
}

void	next_intersection_y(t_vector prev, t_player player)
{
	t_vector	next;
	int			len;

	next.y = prev.y + GRID_SIZE * player.pov.quadrant.y;
	next.x = prev.x + GRID_SIZE / tan(player.pov.angle) * player.pov.quadrant.y;
	len = (int)hypot(next.x - prev.x, next.y - prev.y);	
	draw_intersect(player, prev, next, len, HEX_GREEN - 0x00000088);
	draw_point(player.mlx_view, next, HEX_GREEN - 0x00000088);
}

void	first_intersections(t_player player, t_vector grid_distance)
{
	t_vector	pos;
	t_vector	grid;
	int			len;

	pos = get_player_pos(PLAYER_PIXEL_CENTER);
	grid.x = grid_distance.x;
	if (player.pov.quadrant.y == 0)
		grid.y = pos.y;
	else
		grid.y = pos.y + (grid_distance.x - pos.x) * tan(player.pov.angle);
	len = (int)hypot(grid.x - pos.x, grid.y - pos.y);
	draw_intersect(player, pos, grid, len, HEX_RED);
	next_intersection_x(grid, player);
	grid.y = grid_distance.y;
	if (player.pov.quadrant.x == 0)
		grid.x = pos.x;
	else
		grid.x = pos.x + (grid_distance.y - pos.y) / tan(player.pov.angle);
	len = (int)hypot(grid.x - pos.x, grid.y - pos.y);
	draw_intersect(player, pos, grid, len, HEX_GREEN);
	next_intersection_y(grid, player);
}

void	update_mlx_view(t_player player, t_vector grid_distance)
{
	mlx_clear_image(player.mlx_view);
	first_intersections(player, grid_distance);
}
