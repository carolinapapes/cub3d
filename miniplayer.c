/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/02/12 08:48:17 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <string.h>

mlx_image_t	*player_manager(mlx_t *mlx, int x, int y, int flag)
{
	static mlx_image_t	*image;

	if (flag != SET_PLAYER)
		return (image);
	image = mlx_add_image(mlx, PLAYER_SIZE, PLAYER_SIZE, (int[]){x, y + HEIGHT});
	memset(image->pixels, PLAYER_COLOR, image->width * image->height * sizeof(int32_t));
	return (image);
}

mlx_image_t	*get_player(void)
{
	return (player_manager(NULL, 0, 0, 0));
}

void	set_player(mlx_t *mlx, int x, int y)
{
	x = x * GRID_SIZE + PLAYER_SIZE / 2;
	y = y * GRID_SIZE + PLAYER_SIZE / 2;
	player_manager(mlx, x, y, SET_PLAYER);
	get_view(mlx);
	view_rotate(0);
}

int	minicollition_check(int *player, int axis, int dir)
{
	int	movement_size;

	movement_size = 2;
	while (movement_size)
	{
		if (dir == POSITIVE)
			player[axis] += PLAYER_SIZE - 1;
		player[axis] += dir * -1;
		player[axis] += movement_size * dir;
		if (is_fixed_object(player[X], player[Y]) & WALL)
			movement_size--;
		else
			break ;
	}
	return (dir * movement_size);
}

void	miniplayer_hook(int axis, int sign)
{
	mlx_image_t	*player_mlx;
	int			movement_size;
	int			player[2];

	player_mlx = get_player();
	player[X] = player_mlx->instances[0].x;
	player[Y] = player_mlx->instances[0].y - HEIGHT;
	movement_size = minicollition_check(player, axis, sign);
	if (!movement_size)
		return ;
	if (axis == X)
	{
		player_mlx->instances[0].x += movement_size;
		view_move(movement_size, 0);
	}
	if (axis == Y)
	{
		player_mlx->instances[0].y += movement_size;
		view_move(0, movement_size);
	}
}
