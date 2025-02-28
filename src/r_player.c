/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 19:21:20 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	update_minimap_pos(t_vector position, t_vector position_delta)
{
	mlx_image_t	*image;
	t_vector	constants;

	image = get_minimap_image();
	constants = game_constants().limit_movement;
	if (position.x <= constants.x)
		update_mlx_miniplayer_pos(position_delta, X);
	else
		image->instances[0].x -= position_delta.x;
	if (position.y <= constants.y)
		update_mlx_miniplayer_pos(position_delta, Y);
	else
		image->instances[0].y -= position_delta.y;
}

static void	update_pos(t_player *player, t_vector position)
{
	player->pos.x += position.x;
	player->pos.y += position.y;
	update_minimap_pos(player->pos, position);
}

static void	update_pov(t_player *player, double angle_delta)
{
	t_vector	origin;

	mlx_clear_image(get_miniview_image());
	mlx_clear_image(get_render_image());
	player->pov += angle_delta * M_PI / 180;
	if (player->pov > 2 * M_PI)
		player->pov -= 2 * M_PI;
	if (player->pov < 0)
		player->pov += 2 * M_PI;
	origin = get_player_pos(PIXEL | CENTER);
	pov_iter(origin, player->pov);
}

t_player	set_player(t_vector position_delta, double angle_delta)
{
	static t_player	player;

	if (!player.initilized)
	{
		player.initilized = 1;
		player.pos.x = 0;
		player.pos.y = 0;
	}
	if ((int)position_delta.x || (int)position_delta.y)
		update_pos(&player, position_delta);
	if ((int)position_delta.x || (int)position_delta.y || angle_delta)
		update_pov(&player, angle_delta);
	return (player);
}

t_player	get_player(void)
{
	t_player	player;
	t_vector	pos;

	memset(&pos, 0, sizeof(t_vector));
	player = set_player(pos, 0);
	return (player);
}

t_vector	get_player_pos(int flag)
{
	t_player	player;
	t_vector	pos;

	player = get_player();
	pos = player.pos;
	if (flag & CENTER_X)
		pos.x = pos.x + PLAYER_MIDDLE;
	if (flag & CENTER_Y)
		pos.y = pos.y + PLAYER_MIDDLE;
	if (!(flag & PIXEL))
	{
		pos.x = pos.x / GRID_SIZE;
		pos.y = pos.y / GRID_SIZE;
	}
	return (pos);
}
