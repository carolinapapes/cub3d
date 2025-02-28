/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 01:30:50 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	update_pos(t_player *player, t_vector position)
{
	mlx_image_t	*image;

	image = get_minimap_image();
	player->pos.x += position.x;
	player->pos.y += position.y;
	if (player->pos.x <= WIDTH - GRID_SIZE - PLAYER_SIZE)
		update_mlx_player(position, X);
	else
		image->instances[0].x -= position.x;
	if (player->pos.y <= HEIGHT - GRID_SIZE - PLAYER_SIZE)
		update_mlx_player(position, Y);
	else
		image->instances[0].y -= position.y;
}

static void	update_pov(t_player *player, double angle_delta)
{
	t_vector		origin;

	if (player->pos.x <= WIDTH - GRID_SIZE - PLAYER_SIZE
		|| player->pos.y <= HEIGHT - GRID_SIZE - PLAYER_SIZE)
	{
		mlx_clear_image(get_view_image());
		mlx_clear_image(get_aux_img());
	}
	mlx_clear_image(get_render_image());
	player->pov += angle_delta * M_PI / 180;
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
