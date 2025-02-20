/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:25 by capapes           #+#    #+#             */
/*   Updated: 2025/02/20 19:01:45 by capapes          ###   ########.fr       */
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
	if (parser(argc, argv) == NULL)
		return (print_error(), EXIT_FAILURE);
	minimap_init();
	player_init();
	cub3d_init();
	return (EXIT_SUCCESS);
}
