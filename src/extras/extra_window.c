/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:25:37 by capapes           #+#    #+#             */
/*   Updated: 2025/03/18 18:53:52 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*player_info_background(void)
{
	static mlx_image_t	*background;
	t_vector			coord;

	if (!background)
	{
		coord.x = 800;
		background = get_image_full();
		if (!background)
			clean_exit(TERMINATE_MLX | FREE_START);
		while (coord.x < background->width)
		{
			coord.y = 0;
			while (coord.y < background->height)
			{
				set_pixel(background, coord, 0xFFFFFFFF);
				coord.y++;
			}
			coord.x++;
		}
	}
	return (background);
}

mlx_image_t	*get_player_info(void)
{
	static mlx_image_t	*image;

	if (!image)
	{
		image = get_image_full();
		circle(920, 920, 80, image);
	}
	return (image);
}

mlx_image_t	*get_player_view(void)
{
	static mlx_image_t	*mlx_aux;

	if (!mlx_aux)
	{
		player_info_background();
		get_player_info();
		mlx_aux = get_image_full();
	}
	return (mlx_aux);
}

void	draw_line_player_view(t_vector direction)
{
	t_vector	mid;
	mlx_image_t	*image;

	image = get_player_view();
	clear_pixels(image);
	mid.x = 920;
	mid.y = 920;
	draw_line(mid, direction, 80, 0xFF0000FF, image);
}
