/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/03/11 18:50:42 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <unistd.h>

// // Function to calculate delta Y for a given angle
// double	delta_y(double theta_deg)
// {
// 	double	theta_rad;
// 	double	sec_squared;
// 	double	delta_theta_rad;

// 	theta_rad = theta_deg * (M_PI / 180.0);
// 	sec_squared = 1.0 / (cos(theta_rad) * cos(theta_rad));
// 	delta_theta_rad = M_PI / 180.0;
// 	return (sec_squared * delta_theta_rad);
// }

// double	*get_angle_sec(void)
// {
// 	static double	angle_sec[WIDTH];
// 	int				i;
// 	double			angle;

// 	if (!angle_sec[0])
// 	{
// 		i = 0;
// 		while (i < WIDTH)
// 		{
// 			angle_sec[i] = atan((double)(i - WIDTH / 2) / HEIGHT);
// 			i++;
// 		}
// 	}
// 	return (angle_sec);
// }

t_constants	game_constants(void)
{
	static t_constants	constants;

	if (!constants.angle_step)
	{
		constants.fov = 60;
		constants.angle_step = ((double)constants.fov / WIDTH) * M_PI / 180;
		constants.strip_width = 1;
		constants.strip_height = HEIGHT * 10;
		constants.fov_delta_start = -31.0 * M_PI / 180;
		constants.dir_y.x = 0;
		constants.dir_y.y = 1;
		constants.dir_x.x = 1;
		constants.dir_x.y = 0;
		constants.limit_movement.x = WIDTH - GRID_SIZE - PLAYER_SIZE;
		constants.limit_movement.y = HEIGHT - GRID_SIZE - PLAYER_SIZE;
		constants.zero.x = 0;
		constants.zero.y = 0;
		constants.double_pi = 2 * M_PI;
	}
	return (constants);
}

void	print_error(void)
{
	write(2, "Error\n", 6);
	return ;
}

t_start	*get_start(void)
{
	static t_start	start;

	return (&start);
}

void	clean_exit(int flags)
{
	mlx_t	*mlx;
	t_start	*start;

	if (flags & TERMINATE_MLX)
	{
		mlx = get_mlx();
		mlx_terminate(mlx);
	}
	if (flags & FREE_START)
	{
		start = get_start();
		free_start(start);
	}
	exit(EXIT_FAILURE);
}

void	initialize_start(t_start **start)
{
	(*start)->n_fd = NULL;
	(*start)->s_fd = NULL;
	(*start)->w_fd = NULL;
	(*start)->e_fd = NULL;
	(*start)->map.map = NULL;
	(*start)->map.map_int = NULL;
	(*start)->ceiling.rgba = 0;
	(*start)->floor.rgba = 0;
}

int	main(int argc, char **argv)
{
	t_start	*start;

	start = get_start();
	if (!start || argc != 2)
		return (1);
	initialize_start(&start);
	if (parser_controler(argv[1], start) == 1)
	{
		printf("parser dio caca\n");
		free_start(start);
		return (print_error(), EXIT_FAILURE);
	}
	cub3d_init();
	free_start(start);
	return (EXIT_SUCCESS);
}
