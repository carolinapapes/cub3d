/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_render_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:03:16 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 22:23:40 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*get_render_image(void)
{
	static mlx_image_t	*mlx_render;

	if (!mlx_render)
		mlx_render = new_image_full();
	return (mlx_render);
}

void	set_background(mlx_image_t	*mlx_background)
{
	t_vector			origin;

	origin = game_constants().zero;
	while (origin.y < HEIGHT)
	{
		origin.x = 0;
		while (origin.x < WIDTH)
		{
			if (origin.y < HEIGHT_MIDDLE)
				draw_pixel(mlx_background, origin, HEX_CEILING);
			else
				draw_pixel(mlx_background, origin, HEX_FLOOR);
			origin.x++;
		}
		origin.y++;
	}
}

void	init_background(void)
{
	mlx_image_t	*mlx_background;

	mlx_background = new_image_full();
	set_background(mlx_background);
}
