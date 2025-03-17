/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:28:50 by capapes           #+#    #+#             */
/*   Updated: 2025/03/15 09:21:28 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static t_vector	get_initial_pos(t_int_pair initial)
{
	t_vector	pos;

	pos.x = (initial.x + 0.25) * GRID_SIZE;
	pos.y = (initial.y + 0.25) * GRID_SIZE;
	return (pos);
}

static double	get_initial_pov(int initial)
{
	double	pov;

	if (initial == 'E')
		pov = 0;
	else if (initial == 'S')
		pov = 0.5 * M_PI;
	else if (initial == 'W')
		pov = M_PI;
	else
		pov = 1.5 * M_PI;
	return (pov);
}

static t_player	player_constants(t_constants *constants)
{
	t_player	player;

	constants->player_size = rectangle_vector(PLAYER_SIZE);
	constants->player_size_half = rectangle_vector(PLAYER_SIZE / 2);
	player.pos = get_initial_pos(get_start()->player_pos);
	player.pos_center = vector_sum(player.pos,
			game_constants().player_size_half);
	player.pov = get_initial_pov(get_start()->player_dir);
	constants->player_initial = player;
	return (player);
}

static void	texture_constants(t_constants *constants, t_start *start)
{
	constants->textures[NORTH_TEXTURE] = load_png(start->n_fd);
	constants->textures[SOUTH_TEXTURE] = load_png(start->s_fd);
	constants->textures[WEST_TEXTURE] = load_png(start->w_fd);
	constants->textures[EAST_TEXTURE] = load_png(start->e_fd);
}

t_constants	game_constants(void)
{
	static t_constants	constants;
	t_start				*start;

	start = get_start();
	if (!constants.angle_step)
	{
		constants.fov = 60;
		constants.angle_step = ((double)constants.fov / WINDOW_SIZE) * M_PI
			/ 180;
		constants.rotation_delta = constants.angle_step * 60;
		constants.strip_height = WINDOW_SIZE * 25;
		constants.fov_delta_start = -31.0 * M_PI / 180;
		constants.limit_movement = rectangle_vector(WINDOW_SIZE - PLAYER_SIZE);
		constants.window_size = rectangle_vector(WINDOW_SIZE);
		constants.zero = rectangle_vector(0);
		constants.double_pi = 2 * M_PI;
		constants.map_size_px = set_components(start->map.size_int.x
				* GRID_SIZE, start->map.size_int.y * GRID_SIZE);
		constants.map_size = set_components(start->map.size_int.x,
				start->map.size_int.y);
		texture_constants(&constants, start);
		player_constants(&constants);
	}
	return (constants);
}
