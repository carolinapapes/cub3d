/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_minimap_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:56:22 by capapes           #+#    #+#             */
/*   Updated: 2025/03/12 18:50:16 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static mlx_image_t	*init_minimap_image(void)
{
	t_constants	constants;
	mlx_image_t	*image;

	constants = game_constants();
	image = get_image(constants.map_size_px, constants.zero);
	return (image);
}

static void	draw_minimap(t_vector coord)
{
	int			content;
	mlx_image_t	*image;

	image = get_minimap_image();
	content = get_cell_content(coord);
	if (content == OUTSIDE)
		return ;
	if (coord.x && coord.y)
		mlx_put_pixel(image, (uint32_t)coord.x * GRID_SIZE, (uint32_t)coord.y
			* GRID_SIZE, HEX_GRID);
	if (content == WALL)
		coordinate_paint((int)coord.x, (int)coord.y);
}

mlx_image_t	*get_minimap_image(void)
{
	static mlx_image_t	*minimap;
	t_constants			constants;

	if (!minimap)
	{
		minimap = init_minimap_image();
		constants = game_constants();
		generic_matrix_iter(constants.map_size, draw_minimap);
	}
	return (minimap);
}

void	toggle_minimap_visibility(void)
{
	static int			visible = 1;

	visible = !visible;
	get_minimap_image()->enabled = visible;
	get_miniplayer_image()->enabled = visible;
	get_miniview_image()->enabled = visible;
}
