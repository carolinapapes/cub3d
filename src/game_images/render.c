/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:03:16 by capapes           #+#    #+#             */
/*   Updated: 2025/03/13 14:46:31 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

mlx_image_t	*get_render(void)
{
	static mlx_image_t	*mlx_render;

	if (!mlx_render)
		mlx_render = get_image_full();
	return (mlx_render);
}

mlx_image_t	*get_shadow(void)
{
	static mlx_image_t	*mlx_shadow;

	if (!mlx_shadow)
		mlx_shadow = get_image_full();
	return (mlx_shadow);
}

static mlx_image_t	*get_background(void)
{
	static mlx_image_t	*mlx_background;

	if (!mlx_background)
		mlx_background = get_image_full();
	return (mlx_background);
}

static void	set_background_px(t_vector coord)
{
	mlx_image_t	*mlx_background;
	t_start		*start;

	start = get_start();
	mlx_background = get_background();
	if (coord.y < HEIGHT_MIDDLE)
		set_pixel(mlx_background, coord, start->ceiling.rgba);
	else
		set_pixel(mlx_background, coord, start->floor.rgba);
}

void	set_background(void)
{
	t_vector			constraints;

	constraints = game_constants().window_size;
	generic_matrix_iter(constraints, set_background_px);
}
