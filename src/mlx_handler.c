/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:42:23 by capapes           #+#    #+#             */
/*   Updated: 2025/02/20 19:00:58 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	cub3d_hook(void *param)
{
	mlx_t		*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		player_hook(Y, NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player_hook(Y, POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player_hook(X, NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player_hook(X, POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		view_rotate(NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		view_rotate(POSITIVE);
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
	if (mlx_loop_hook(mlx, cub3d_hook, mlx) == -1)
		exit(1);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
