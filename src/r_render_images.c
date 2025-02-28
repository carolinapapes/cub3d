/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _aux_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:03:16 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 17:04:31 by capapes          ###   ########.fr       */
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

void	init_background_colors(mlx_image_t	*mlx_background)
{
	t_vector			origin;

	ft_memset(&origin, 0, sizeof(t_vector));
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

mlx_image_t	*get_background_image(void)
{
	static mlx_image_t	*mlx_background;

	if (!mlx_background)
	{
		mlx_background = new_image_full();
		init_background_colors(mlx_background);
	}
	return (mlx_background);
}
