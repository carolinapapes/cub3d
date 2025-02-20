/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/02/20 19:10:11 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// THIS FUNCTION WILL BE REMOVED AND REPLACED BY THE PARSER RESULT
t_vector	map_find_player(void)
{
	t_vector	pos;
	int			**map;

	map = get_map();
	pos = (t_vector){MAP_SIZE_X, MAP_SIZE_Y};
	while ((pos.x)-- && !map[(int)pos.y][(int)pos.x] & PLAYER)
	{
		if (!pos.x && pos.y)
		{
			pos.x = MAP_SIZE_X;
			pos.y--;
		}
	}
	return (pos);
}

mlx_image_t	*init_player_image(void)
{
	t_vector	size;
	mlx_image_t	*image;

	size.x = PLAYER_SIZE;
	size.y = PLAYER_SIZE;
	image = new_image(size, (t_vector){0, 0});
	image_full_color(image, PLAYER_COLOR);
	return (image);
}

void	update_player_pos(t_player *player, t_vector position)
{
	player->pos.x += position.x;
	player->pos.y += position.y;
	player->image->instances[0].x = player->pos.x * GRID_SIZE;
	player->image->instances[0].y = player->pos.y * GRID_SIZE;
}

t_player	set_player(t_vector position_delta)
{
	static t_player	player;

	if (!player.image)
		player.image = init_player_image();
	if ((int)position_delta.x || (int)position_delta.y)
		update_player_pos(&player, position_delta);
	set_view();
	return (player);
}

t_player	player_init(void)
{
	t_vector	initial_pos;

	initial_pos = map_find_player();
	set_player(initial_pos);
}

t_vector	get_player_pos(void)
{
	t_player	player;

	player = set_player((t_vector){0, 0});
	return (player.pos);
}
