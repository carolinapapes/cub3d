/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 15:50:49 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <unistd.h>

t_start	*get_start(void)
{
	static t_start	start;

	return (&start);
}

void	cub3d_init(void)
{
	set_background();
	set_render();
	set_minimap();
	set_minimap_pos(game_constants().zero);
	loop_window(cub3d_hook);
}

int	main(int argc, char **argv)
{
	t_start	*start;

	start = get_start();
	if (!start || argc != 2)
		return (1);
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
