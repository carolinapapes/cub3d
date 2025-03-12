/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:42:23 by capapes           #+#    #+#             */
/*   Updated: 2025/02/20 19:00:58 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	cub3d_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		player_move(Y, POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player_move(Y, NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player_move(X, NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player_move(X, POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player_rotate(NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player_rotate(POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_L))
		set_timeout(toggle_minimap_visibility, 300);
}

void	cub3d_init(void)
{
	set_background_image();
	load_texture_images();
	get_minimap_image();
	init_player();
	loop_window(cub3d_hook);
}
