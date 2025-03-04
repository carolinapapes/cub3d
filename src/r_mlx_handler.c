/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mlx.c                                      :+:      :+:    :+:   */
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
	mlx_t		*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		player_move(Y, NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player_move(Y, POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player_move(X, NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player_move(X, POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		player_rotate(NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player_rotate(POSITIVE);
}

mlx_t	*get_mlx(void)
{
	static mlx_t	*mlx;

	if (!mlx)
		mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, true);
	if (!mlx)
		exit(1);
	return (mlx);
}

void	cub3d_init(void)
{
	mlx_t		*mlx;

	mlx = get_mlx();
	init_background();
	init_minimap();
	init_player();
	if (mlx_loop_hook(mlx, cub3d_hook, mlx) == 0)
		exit(1);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
