/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _aux_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:03:16 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 13:54:49 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*get_miniplayer_image(void)
{
	t_vector			size;
	t_vector			origin;
	static mlx_image_t	*image;

	if (!image)
	{
		origin.x = 0;
		origin.y = 0;
		size.x = PLAYER_SIZE;
		size.y = PLAYER_SIZE;
		image = new_image(size, origin);
		image_full_color(image, HEX_PLAYER);
	}
	return (image);
}

mlx_image_t	*get_minimap_image(void)
{
	static mlx_image_t	*mlx_minimap;
	t_start				*start;
	t_vector			size;
	t_vector			origin;

	if (!mlx_minimap)
	{
		start = get_start();
		size.x = start->map.size_int.x * GRID_SIZE;
		size.y = start->map.size_int.y * GRID_SIZE;
		ft_memset(&origin, 0, sizeof(t_vector));
		mlx_minimap = new_image(size, origin);
	}
	return (mlx_minimap);
}

mlx_image_t	*get_aux_img(void)
{
	static mlx_image_t	*mlx_aux;

	if (!mlx_aux)
		mlx_aux = new_image_full();
	return (mlx_aux);
}

mlx_image_t	*get_render_image(void)
{
	static mlx_image_t	*mlx_render;

	if (!mlx_render)
		mlx_render = new_image_full();
	return (mlx_render);
}

mlx_image_t	*get_background_image(void)
{
	static mlx_image_t	*mlx_background;
	t_vector			origin;

	if (!mlx_background)
	{
		mlx_background = new_image_full();
		origin.y = 0;
		origin.x = 0;
		while (origin.y < HEIGHT)
		{
			origin.x = 0;
			while (origin.x < WIDTH)
			{
				if (origin.y < HEIGHT / 2)
					mlx_put_pixel(mlx_background, origin.x, origin.y, HEX_CEILING);
				else
					mlx_put_pixel(mlx_background, origin.x, origin.y, HEX_FLOOR);
				origin.x++;
			}
			origin.y++;
		}
	}
	return (mlx_background);
}
