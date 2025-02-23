/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus_remove_later.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:21:30 by capapes           #+#    #+#             */
/*   Updated: 2025/02/23 19:28:28 by capapes          ###   ########.fr       */
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

t_vector	intersection(t_pov pov, t_vector grid,
	t_axis axis, t_vector origin)
{
	t_vector		next;

	if (pov.quadrant.arr[!axis] == 0)
		return (origin);
	if (axis == Y)
		pov.tan = 1 / pov.tan;
	next.arr[axis] = grid.arr[axis];
	next.arr[!axis] = origin.arr[!axis] + (grid.arr[axis] - origin.arr[axis]) * pov.tan;
	return (next);
}

void	update_mlx_view(t_player player, t_vector grid_distance)
{
	t_vector	origin;
	t_vector	intersect;
	t_vector	grid_delta;

	mlx_clear_image(player.mlx_view);
	origin = get_player_pos(PLAYER_PIXEL_CENTER);
	intersect = intersection(player.pov, grid_distance, X, origin);
	draw_intersect(player, origin, intersect, HEX_RED);
	grid_delta.x = GRID_SIZE * player.pov.quadrant.x + intersect.x;
	grid_delta.y = GRID_SIZE * player.pov.quadrant.y + intersect.y;
	intersect = intersection(player.pov, grid_delta, X, intersect);
	draw_intersect(player, origin, intersect, HEX_RED - 0x00000088);
	intersect = intersection(player.pov, grid_distance, Y, origin);
	draw_intersect(player, origin, intersect, HEX_GREEN);
	grid_delta.x = GRID_SIZE * player.pov.quadrant.x + intersect.x;
	grid_delta.y = GRID_SIZE * player.pov.quadrant.y + intersect.y;
	intersect = intersection(player.pov, grid_delta, Y, intersect);
	draw_intersect(player, origin, intersect, HEX_GREEN - 0x00000088);
}
