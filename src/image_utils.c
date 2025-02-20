/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:21:45 by capapes           #+#    #+#             */
/*   Updated: 2025/02/20 17:21:53 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	iter_image(mlx_image_t *image, void fn(mlx_image_t *, uint32_t,
			uint32_t))
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			fn(image, x, y);
			x++;
		}
		y++;
	}
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	image_full_color(mlx_image_t *image, int32_t color)
{
	memset(image->pixels, color, image->width * image->height
		* sizeof(int32_t));
}

void	mlx_clear_image(mlx_image_t *image)
{
	image_full_color(image, 0x00000000);
}
