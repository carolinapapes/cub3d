/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/02/12 08:46:25 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_hook(void *param)
{
	mlx_t		*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		miniplayer_hook(Y, NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		miniplayer_hook(Y, POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		miniplayer_hook(X, NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		miniplayer_hook(X, POSITIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		view_rotate(NEGATIVE);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		view_rotate(POSITIVE);
}

int32_t	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT * 2, WINDOW_TITLE, true);
	if (!mlx)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	set_minimap(mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

// TODO
// - Create structure mvp needed for the project
