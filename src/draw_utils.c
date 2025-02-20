/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:31:42 by capapes           #+#    #+#             */
/*   Updated: 2025/02/20 16:37:14 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_pixel(mlx_image_t *image, t_vector pixel, int32_t color)
{
	mlx_put_pixel(image, pixel.x, pixel.y, color);
}

void	draw_cross(mlx_image_t *image, t_vector point)
{
	int	offset;

	offset = 5;
	while (offset-- > -5)
	{
		mlx_put_pixel(image, point.x + offset, point.y, 0x00FF00FF);
		mlx_put_pixel(image, point.x, point.y + offset, 0x00FF00FF);
	}
}

// TODO: check if mlx add pixel is needed 
// for each increment of length in draw_line
void	draw_line(mlx_image_t *image, t_vector origin,
	t_vector direction, int len)
{
	t_vector	pixel;

	while (len--)
	{
		pixel.x = origin.x + direction.x * len;
		pixel.y = origin.y + direction.y * len;
		draw_pixel(image, pixel, 0xFF0000FF);
	}
}
