/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/03/13 19:50:50 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_player	init_player(void)
{
	t_constants	constants;
	t_player	player;

	constants = game_constants();
	player.pos = constants.initial_pos;
	player.pos_center.x = player.pos.x + PLAYER_MIDDLE;
	player.pos_center.y = player.pos.y + PLAYER_MIDDLE;
	player.pov = constants.initial_pov;
	return (player);
}

t_player	*get_player(void)
{
	static t_player	player;

	if (!player.pos.x)
		player = init_player();
	return (&player);
}

void	set_player_pos(t_vector delta)
{
	t_player	*player;

	player = get_player();
	player->pos.x += delta.x;
	player->pos.y += delta.y;
	player->pos_center.x += delta.x;
	player->pos_center.y += delta.y;
}

void	set_player_pov(double dir)
{
	t_constants	constants;
	t_player	*player;

	player = get_player();
	constants = game_constants();
	player->pov += dir * constants.rotation_delta;
	player->pov = radian_overflow(player->pov);
}

void	update_render(void)
{
	t_player	*player;

	player = get_player();
	pov_iter(player->pos_center, player->pov);
}
