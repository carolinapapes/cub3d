/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 18:14:11 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	update_pos(t_player *player, t_vector position)
{
	player->pos.x += position.x;
	player->pos.y += position.y;
	update_mlx_player();
}

static void	update_pov(t_player *player, double angle_delta)
{
	t_vector		origin;

	mlx_clear_image(get_view_image());
	mlx_clear_image(get_aux_img());
	mlx_clear_image(get_render_image());
	player->pov += angle_delta * M_PI / 180;
	origin = get_player_pos(PIXEL | CENTER);
	pov_iter(origin, player->pov);
}

t_player	set_player(t_vector position_delta, double angle_delta)
{
	static t_player	player;

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
