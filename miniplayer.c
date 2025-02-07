/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/02/07 19:08:06 by capapes          ###   ########.fr       */
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
}

int			g_map2[16][16] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int	minicollition_check(int x, int y, int axis, int dir)
{
	printf("dir: %d \t axis %d\n", dir, axis);
	if (axis == X)
		x += dir * (PLAYER_SIZE / 2);
	if (axis == Y)
		y += dir * (PLAYER_SIZE / 2);
	printf("x: %d \t y: %d\n", x, y);
	printf("G: %d, %d\n", y / GRID_SIZE, x / GRID_SIZE);
	if (g_map2[y / GRID_SIZE][x / GRID_SIZE] == 1)
		return (1);
	return (0);
}

void	miniplayer_hook(int axis, int sign)
{
	mlx_image_t	*player;

	player = get_player();
	if (minicollition_check(player->instances[0].x, player->instances[0].y
			- HEIGHT, axis, sign))
		return ;
	if (axis == X)
		player->instances[0].x += sign * 2;
	if (axis == Y)
		player->instances[0].y += sign * 2;
}
