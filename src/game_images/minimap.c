/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:56:22 by capapes           #+#    #+#             */
/*   Updated: 2025/03/13 14:47:23 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static mlx_image_t	*init_minimap(void)
{
	t_constants	constants;
	mlx_image_t	*image;

	constants = game_constants();
	image = get_image(constants.map_size_px, constants.zero);
	return (image);
}

mlx_image_t	*get_minimap(void)
{
	static mlx_image_t	*minimap;

	if (!minimap)
		minimap = init_minimap();
	return (minimap);
}

static void	set_minimap_px(t_vector coord)
{
	int			content;
	mlx_image_t	*image;

	image = get_minimap();
	content = get_cell_content(coord);
	if (content == OUTSIDE)
		return ;
	if (coord.x && coord.y)
		mlx_put_pixel(image, (uint32_t)coord.x * GRID_SIZE, (uint32_t)coord.y
			* GRID_SIZE, HEX_GRID);
	if (content == WALL)
		coordinate_paint((int)coord.x, (int)coord.y);
}

void	set_minimap(void)
{
	t_constants	constants;

	constants = game_constants();
	generic_matrix_iter(constants.map_size, set_minimap_px);
}

void	toggle_minimap(void)
{
	static int			visible = 1;

	visible = !visible;
	get_minimap()->enabled = visible;
	get_miniplayer()->enabled = visible;
	get_miniview()->enabled = visible;
}
