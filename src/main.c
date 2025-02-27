/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 11:16:19 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <unistd.h>

t_constants	game_constants(void)
{
	static t_constants	constants;

	if (!constants.angle_step)
	{
		constants.fov = 60;
		constants.angle_step = M_PI / 180;
		constants.wall_strip_width = WIDTH / constants.fov;
		constants.wall_strip_height = (HEIGHT * 150);
		constants.fov_delta_start = -31.0 * constants.angle_step;
		constants.dir_y.x = 0;
		constants.dir_y.y = 1;
		constants.dir_x.x = 1;
		constants.dir_x.y = 0;
	}
	return (constants);
}

void	print_error(void)
{
	write(2, "Error\n", 6);
	return ;
}

int32_t	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	minimap_init();
	player_init();
	cub3d_init();
	return (EXIT_SUCCESS);
}
