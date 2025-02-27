/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 19:32:36 by capapes          ###   ########.fr       */
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
		constants.strip_width = WIDTH / constants.fov;
		constants.strip_height = (HEIGHT * 150);
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
	get_minimap_image(start);
	player_init(start);
	cub3d_init();
	free_start(start);
	// free(start);
	return (EXIT_SUCCESS);
}
