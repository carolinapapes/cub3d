/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/02/21 17:52:35 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <unistd.h>

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
