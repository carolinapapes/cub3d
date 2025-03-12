/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_render_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:03:16 by capapes           #+#    #+#             */
/*   Updated: 2025/03/12 20:17:12 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*get_render_image(void)
{
	static mlx_image_t	*mlx_render;

	if (!mlx_render)
		mlx_render = get_full_image();
	return (mlx_render);
}

mlx_image_t	*get_shadow_image(void)
{
	static mlx_image_t	*mlx_shadow;

	if (!mlx_shadow)
		mlx_shadow = get_full_image();
	return (mlx_shadow);
}

mlx_image_t	*get_background_image(void)
{
	static mlx_image_t	*mlx_background;

	if (!mlx_background)
		mlx_background = get_full_image();
	return (mlx_background);
}

static void	set_background_color(t_vector coord)
{
	mlx_image_t	*mlx_background;
	t_start		*start;

	start = get_start();
	mlx_background = get_background_image();
	if (coord.y < HEIGHT_MIDDLE)
		set_pixel(mlx_background, coord, start->ceiling.rgba);
	else
		set_pixel(mlx_background, coord, start->floor.rgba);
}

void	set_background_image(void)
{
	t_vector	constraints;

	constraints = game_constants().window_size;
	generic_matrix_iter(constraints, set_background_color);
}
