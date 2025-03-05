/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_minimap_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:56:22 by capapes           #+#    #+#             */
/*   Updated: 2025/03/05 14:55:53 by capapes          ###   ########.fr       */
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
	t_vector			zero;

	start = get_start();
	size.x = start->map.size_int.x * GRID_SIZE;
	size.y = start->map.size_int.y * GRID_SIZE;
	zero = game_constants().zero;
	return (new_image(size, zero));
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

void	init_minimap(void)
{
	t_start				*start;
	t_vector			size;

	start = get_start();
	size.x = start->map.size_int.x;
	size.y = start->map.size_int.y;
	generic_matrix_iter(size, draw_minimap);
}
