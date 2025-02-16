/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:21:45 by capapes           #+#    #+#             */
/*   Updated: 2025/02/16 17:39:09 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	iter_image(mlx_image_t *image, void(fn)(mlx_image_t *, uint32_t,
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

void	mlx_clear_image(mlx_image_t *image)
{
	memset(image->pixels, 0x00FF00BB, image->width * image->height
		* sizeof(int32_t));
}

mlx_image_t	*mlx_add_image(mlx_t *mlx, uint32_t width, uint32_t height, int *pos)
{
	mlx_image_t	*image;

	image = mlx_new_image(mlx, width, height);
	if (mlx_image_to_window(mlx, image, pos[X], pos[Y]) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		exit(1);
	}
	return (image);
}
