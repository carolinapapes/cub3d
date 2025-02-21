/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus_remove_later.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:21:30 by capapes           #+#    #+#             */
/*   Updated: 2025/02/21 20:13:29 by capapes          ###   ########.fr       */
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

void	update_mlx_view(t_player player, t_vector grid_distance)
{
	t_vector	pos;
	t_vector	len_to_x;
	t_vector	len_to_y;


	pos = get_player_pos(PLAYER_PIXEL_CENTER);
	mlx_clear_image(player.mlx_view);
	len_to_x.x = grid_distance.x;
	if (player.pov.quadrant.y == 0)
		len_to_x.y = pos.y;
	else
		len_to_x.y = pos.y + (grid_distance.x - pos.x) * tan(player.pov.angle);
	len_to_y.y = grid_distance.y;
	if (player.pov.quadrant.x == 0)
		len_to_y.x = pos.x;
	else
		len_to_y.x = pos.x + (grid_distance.y - pos.y) / tan(player.pov.angle);
	draw_line(player.mlx_view, pos, player.pov.t_ratio, 100);
	draw_line(player.mlx_view, pos, player.pov.t_ratio, 100);
	draw_point(player.mlx_view, len_to_x);
	draw_point(player.mlx_view, len_to_y);
}
