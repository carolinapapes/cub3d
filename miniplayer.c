/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/02/11 18:14:01 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <string.h>

mlx_image_t	*player_manager(mlx_t *mlx, int x, int y, int flag)
{
	static mlx_image_t	*image;

	if (flag != SET_PLAYER)
		return (image);
	image = mlx_new_image(mlx, PLAYER_SIZE, PLAYER_SIZE);
	if (!image)
		return (NULL);
	memset(image->pixels, 255, image->width * image->height * sizeof(int32_t));
	x = x * GRID_SIZE + PLAYER_SIZE / 2;
	y = y * GRID_SIZE + PLAYER_SIZE / 2;
	if (mlx_image_to_window(mlx, image, x, y + HEIGHT) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
	}
	return (image);
}

mlx_image_t	*get_player(void)
{
	return (player_manager(NULL, 0, 0, 0));
}

void	set_player(mlx_t *mlx, int x, int y)
{
	player_manager(mlx, x, y, SET_PLAYER);
	get_view(mlx);
	view_move(0, HEIGHT);
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
