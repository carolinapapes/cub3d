/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/03/13 20:47:40 by capapes          ###   ########.fr       */
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
// 	static double	angle_sec[WINDOW_SIZE];
// 	int				i;
// 	double			angle;

// 	if (!angle_sec[0])
// 	{
// 		i = 0;
// 		while (i < WINDOW_SIZE)
// 		{
// 			angle_sec[i] = atan((double)(i - WINDOW_SIZE / 2) / WINDOW_SIZE);
// 			i++;
// 		}
// 	}
// 	return (angle_sec);
// }

t_vector	get_initial_pos(t_int_pair initial)
{
	t_vector	pos;

	pos.x = (initial.x + 0.25) * GRID_SIZE;
	pos.y = (initial.y + 0.25) * GRID_SIZE;
	return (pos);
}

double	get_initial_pov(int initial)
{
	double	pov;

	if (initial == 'E')
		pov = 0;
	else if (initial == 'S')
		pov = 0.5 * M_PI;
	else if (initial == 'W')
		pov = M_PI;
	else
		pov = 1.5 * M_PI;
	return (pov);
}

t_player	player_constants(void)
{
	t_player	player;

	player.pos = get_initial_pos(get_start()->player_pos);
	player.pos_center = vector_sum(player.pos, game_constants().player_size_half);
	player.pov = get_initial_pov(get_start()->player_dir);
	return (player);
}

t_vector	set_components(double a, double b)
{
	t_vector	result;

	result.x = a;
	result.y = b;
	return (result);
}

t_vector	rectangle_vector(double a)
{
	t_vector	result;

	result.x = a;
	result.y = a;
	return (result);
}

t_constants	game_constants(void)
{
	static t_constants	constants;
	t_start				*start;

	start = get_start();
	if (!constants.angle_step)
	{
		constants.fov = 60;
		constants.angle_step = ((double)constants.fov / WINDOW_SIZE) * M_PI / 180;
		constants.rotation_delta = constants.angle_step * 20;
		constants.strip_height = WINDOW_SIZE * 10;
		constants.fov_delta_start = -31.0 * M_PI / 180;
		constants.limit_movement = rectangle_vector(
				WINDOW_SIZE - GRID_SIZE - PLAYER_SIZE);
		constants.window_size = rectangle_vector(WINDOW_SIZE);
		constants.zero = rectangle_vector(0);
		constants.double_pi = 2 * M_PI;
		constants.map_size_px = set_components(
				start->map.size_int.x * GRID_SIZE,
				start->map.size_int.y * GRID_SIZE);
		constants.map_size = set_components(
				start->map.size_int.x,
				start->map.size_int.y);
		constants.textures[NORTH_TEXTURE] = load_png(start->n_fd);
		constants.textures[SOUTH_TEXTURE] = load_png(start->s_fd);
		constants.textures[WEST_TEXTURE] = load_png(start->w_fd);
		constants.textures[EAST_TEXTURE] = load_png(start->e_fd);
		constants.player_size = rectangle_vector(PLAYER_SIZE);
		constants.player_size_half = rectangle_vector(PLAYER_SIZE / 2);
		constants.player_initial = player_constants();
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
		mlx = get_window();
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
	(*start)->ceiling.repeated = -1;
	(*start)->floor.repeated = -1;
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
	game_constants();
	cub3d_init();
	free_start(start);
	return (EXIT_SUCCESS);
}
