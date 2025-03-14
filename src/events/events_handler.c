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

#include "../cube3d.h"

static void	cub3d_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move(Y, POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move(Y, NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move(X, NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move(X, POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate(NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate(POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_L))
		set_timeout(toggle_minimap, 300);
}

void	cub3d_init(void)
{
	set_background();
	set_minimap();
	set_minimap_pos(game_constants().zero);
	set_render();
	loop_window(cub3d_hook);
}
