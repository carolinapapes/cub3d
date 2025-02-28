/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_minimap_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:56:22 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 18:00:23 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*init_miniplayer_image(void)
{
	t_vector			size;
	t_vector			origin;

	origin.x = 0;
	origin.y = 0;
	size.x = PLAYER_SIZE;
	size.y = PLAYER_SIZE;
	return (new_image(size, origin));
}

mlx_image_t	*get_miniplayer_image(void)
{
	static mlx_image_t	*image;

	if (!image)
	{
		image = init_miniplayer_image();
		image_full_color(image, HEX_PLAYER);
	}
	return (image);
}

mlx_image_t	*init_minimap_image(void)
{
	t_start				*start;
	t_vector			size;
	t_vector			origin;

	start = get_start();
	size.x = start->map.size_int.x * GRID_SIZE;
	size.y = start->map.size_int.y * GRID_SIZE;
	ft_memset(&origin, 0, sizeof(t_vector));
	return (new_image(size, origin));
}

mlx_image_t	*get_minimap_image(void)
{
	static mlx_image_t	*mlx_minimap;

	if (!mlx_minimap)
		mlx_minimap = init_minimap_image();
	return (mlx_minimap);
}

mlx_image_t	*get_miniview_image(void)
{
	static mlx_image_t	*mlx_aux;

	if (!mlx_aux)
		mlx_aux = new_image_full();
	return (mlx_aux);
}
