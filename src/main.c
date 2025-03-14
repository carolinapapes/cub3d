/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 15:02:58 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <unistd.h>

t_start	*get_start(void)
{
	static t_start	start;

	return (&start);
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

void	cub3d_init(void)
{
	set_background();
	set_minimap();
	set_minimap_pos(game_constants().zero);
	set_render();
	loop_window(cub3d_hook);
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
