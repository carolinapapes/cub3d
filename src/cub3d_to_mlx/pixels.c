/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:57:39 by capapes           #+#    #+#             */
/*   Updated: 2025/03/13 13:15:43 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	set_pixels(mlx_image_t *image, int32_t color)
{
	memset(image->pixels, color, image->width * image->height
		* sizeof(int32_t));
}

void	clear_pixels(mlx_image_t *image)
{
	set_pixels(image, 0x00000000);
}

void	set_pixel(mlx_image_t *image, t_vector pixel, uint32_t color)
{
	mlx_put_pixel(image, pixel.x, pixel.y, color);
}

uint32_t	get_pixel(uint8_t *pixels, uint32_t index)
{
	t_color	color;

	color.r = pixels[index];
	color.g = pixels[index + 1];
	color.b = pixels[index + 2];
	color.a = pixels[index + 3];
	return (color.rgba);
}
