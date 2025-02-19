/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:41:04 by capapes           #+#    #+#             */
/*   Updated: 2025/02/19 20:30:56 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*player_manager(mlx_t *mlx, int x, int y, int flag)
{
	static mlx_image_t	*image;

	if (flag != SET_PLAYER)
		return (image);
	image = mlx_add_image(mlx, PLAYER_SIZE, PLAYER_SIZE, (int[]){x, y});
	ft_memset(image->pixels, PLAYER_COLOR, image->width * image->height
		* sizeof(int32_t));
	mlx_put_pixel(image, 0, 0, 0xFF0000FF);
	mlx_put_pixel(image, 0, 1, 0xFF0000FF);
	mlx_put_pixel(image, 1, 1, 0xFF0000FF);
	mlx_put_pixel(image, 1, 0, 0xFF0000FF);
	return (image);
}

mlx_image_t	*get_player(void)
{
	return (player_manager(NULL, 0, 0, 0));
}

void	set_player(mlx_t *mlx, t_vector player)
{
	player.x = player.x * GRID_SIZE + PLAYER_SIZE / 2;
	player.y = player.y * GRID_SIZE + PLAYER_SIZE / 2;
	player_manager(mlx, player.x, player.y, SET_PLAYER);
	get_view(mlx);
	view_rotate(0);
}

int	hits_wall(t_vector pos, int axis)
{
	if (is_fixed_object(pos.x, pos.y) & WALL)
		return (1);
	pos.arr[!axis] += PLAYER_SIZE - 1;
	return (is_fixed_object(pos.x, pos.y) & WALL);
}

// TODO: check if negative collition needs one pixel fix
t_vector	minicollition_check(t_vector player, int axis, int dir)
{
	t_vector	moves;

	if (dir == POSITIVE)
		player.arr[axis] += ((PLAYER_SIZE - 1) * dir);
	moves.arr[axis] = 3 * dir;
	player.arr[axis] += moves.arr[axis];
	while (moves.arr[axis] && hits_wall(player, axis))
	{
		moves.arr[axis] -= dir;
		player.arr[axis] -= dir;
	}
		
	return (moves);
}

void	miniplayer_hook(int axis, int sign)
{
	mlx_image_t	*player_mlx;
	t_vector		player;
	t_vector		movement_size;

	player_mlx = get_player();
	player.x = player_mlx->instances[0].x;
	player.y = player_mlx->instances[0].y;
	movement_size = minicollition_check(player, axis, sign);
	player_mlx->instances[0].x += movement_size.x;
	player_mlx->instances[0].y += movement_size.y;
	view_move(movement_size);
}
