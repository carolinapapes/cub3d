/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _aux_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:03:16 by capapes           #+#    #+#             */
/*   Updated: 2025/02/28 00:30:25 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*get_player_image(void)
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

mlx_image_t	*get_view_image(void)
{
	static mlx_image_t	*mlx_view;

	if (!mlx_view)
		mlx_view = new_image_full();
	return (mlx_view);
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
