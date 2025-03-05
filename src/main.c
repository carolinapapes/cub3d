/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/03/05 16:27:15 by capapes          ###   ########.fr       */
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
		// constants.angle_sec = get_angle_sec();
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

int	main(int argc, char **argv)
{
	t_start	*start;

	start = get_start();
	if (!start)
		return (1);
	if (parser_controler(argc, argv, start) == 1)
	{
		free_start(start);
		return (print_error(), EXIT_FAILURE);
	}
	cub3d_init();
	free_start(start);
	return (EXIT_SUCCESS);
}
