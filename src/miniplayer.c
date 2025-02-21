/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/02/21 19:54:57 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_pos(t_player *player, t_vector position)
{
	player->pos.x += position.x;
	player->pos.y += position.y;
	update_mlx_player(player);
}

void	update_pov(t_player *player, double angle_delta)
{
	t_vector	grid_distance;

	player->pov.angle += angle_delta * M_PI / 180;
	player->pov.t_ratio.x = cos(player->pov.angle);
	player->pov.t_ratio.y = sin(player->pov.angle);
	player->pov.quadrant.x = \
		(player->pov.t_ratio.x > 0) - (player->pov.t_ratio.x < 0);
	player->pov.quadrant.y = \
		(player->pov.t_ratio.y > 0) -(player->pov.t_ratio.y < 0);
	grid_distance = get_grid_distance(*player);
	update_mlx_view(*player, grid_distance);
}

/* @brief Set the player position and return the player struct
 * 
 * If player is not initialized, it will be initialized on the first call
 * 
 * @param position_delta The position change of the player
 * @return The player struct
 */
t_player	set_player(t_vector position_delta, double angle_delta)
{
	static t_player	player;

	if (!player.mlx_player)
	{
		player.mlx_player = init_player_image();
		player.mlx_view = get_view();
		player.pov.t_ratio.x = 1;
		player.pov.quadrant.x = 1;
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
	if (flag == PLAYER_PIXEL_CENTER)
	{
		pos.x = pos.x + PLAYER_MIDDLE;
		pos.y = pos.y + PLAYER_MIDDLE;
	}
	return (pos);
}
