/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/02/25 14:39:50 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_hook(void *param)
{
	mlx_t	*mlx;

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

void	print_error(void)
{
	write(2, "Error\n", 6);
	return ;
}

int	main(int argc, char **argv)
{
	//mlx_t	*mlx;
	t_start	*start;

	start = malloc(sizeof(t_start));
	if (!start)
		return (1);
	if (parser_controler(argc, argv, start) == 1)
	{
		//free_start(start);
		free(start);
		return (print_error(), EXIT_FAILURE);
	}
	//mlx = mlx_init(WIDTH, HEIGHT * 2, WINDOW_TITLE, true);
	//if (!mlx)
	//	return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	//set_minimap(mlx);
	//mlx_loop_hook(mlx, ft_hook, mlx);
	//mlx_loop(mlx);
	//mlx_terminate(mlx);
	free_start(start);
	free(start);
	return (EXIT_SUCCESS);
}

// TODO
// - Create structure mvp needed for the project
