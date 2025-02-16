/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/02/16 18:02:26 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*player_manager(mlx_t *mlx, int x, int y, int flag)
{
	static mlx_image_t	*image;

	if (flag != SET_PLAYER)
		return (image);
	image = mlx_add_image(mlx, PLAYER_SIZE, PLAYER_SIZE, (int[]){x, y + HEIGHT});
	ft_memset(image->pixels, PLAYER_COLOR, image->width * image->height * sizeof(int32_t));
	return (image);
}

mlx_image_t	*get_player(void)
{
	return (player_manager(NULL, 0, 0, 0));
}

void	set_player(mlx_t *mlx, t_coord player)
{
	player.x = player.x * GRID_SIZE + PLAYER_SIZE / 2;
	player.y = player.y * GRID_SIZE + PLAYER_SIZE / 2;
	player_manager(mlx, player.x, player.y, SET_PLAYER);
	get_view(mlx);
	view_rotate(0);
}

// TODO: check if negative collition needs one pixel fix
t_coord	minicollition_check(t_coord player, int axis, int dir)
{
	t_coord	movement_size;

	movement_size.arr[axis] = 2 * dir;
	if (dir == POSITIVE)
		player.arr[axis] += PLAYER_SIZE - 1;
	while (movement_size.arr[axis]
		&& is_fixed_object(player.x + movement_size.x, player.y + movement_size.y) & WALL)
		movement_size.arr[axis] -= dir;
	return (movement_size);
}

void	miniplayer_hook(int axis, int sign)
{
	mlx_image_t	*player_mlx;
	t_coord		player;
	t_coord		movement_size;

	player_mlx = get_player();
	player.x = player_mlx->instances[0].x;
	player.y = player_mlx->instances[0].y - HEIGHT;
	movement_size = minicollition_check(player, axis, sign);
	player_mlx->instances[0].x += movement_size.x;
	player_mlx->instances[0].y += movement_size.y;
	view_move(movement_size);
}
