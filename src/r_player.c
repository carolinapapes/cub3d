/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/03/12 18:08:54 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	update_pos(t_player *player, t_vector position)
{
	player->pos.x += position.x;
	player->pos.y += position.y;
	update_minimap_pos(player->pos, position);
}

static void	update_pov(t_player *player, double angle_delta)
{
	t_vector	origin;
	t_constants	constants;

	constants = game_constants();
	if (angle_delta == 1 || angle_delta == -1)
		player->pov += angle_delta * constants.angle_step * 20;
	else
		player->pov += angle_delta;
	player->pov = radian_overflow(player->pov);
	origin = get_player_center_px();
	pov_iter(origin, player->pov);
}

t_player	set_player(t_vector position_delta, double angle_delta)
{
	static t_player	player;

	if (position_delta.x != 0 || position_delta.y != 0)
		update_pos(&player, position_delta);
	if (position_delta.x != 0 || position_delta.y != 0 || angle_delta)
		update_pov(&player, angle_delta);
	return (player);
}

t_player	get_player(void)
{
	return (set_player(game_constants().zero, 0));
}

t_vector	get_player_center_px(void)
{
	t_vector	pos;

	pos = get_player().pos;
	pos.x += PLAYER_MIDDLE;
	pos.y += PLAYER_MIDDLE;
	return (pos);
}

void	init_player(void)
{
	t_vector	initial_pos;
	t_start		*start;

	start = get_start();
	initial_pos.x = (start->player_pos.x + 0.25) * GRID_SIZE;
	initial_pos.y = (start->player_pos.y + 0.25) * GRID_SIZE;
	if (start->player_dir == 'E')
		set_player(initial_pos, 0);
	else if (start->player_dir == 'S')
		set_player(initial_pos, 0.5 * M_PI);
	else if (start->player_dir == 'W')
		set_player(initial_pos, 1 * M_PI);
	else if (start->player_dir == 'N')
		set_player(initial_pos, 1.5 * M_PI);
}
