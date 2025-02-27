/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_mlx_image_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:57:39 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 19:12:14 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	iter_image(mlx_image_t *image, void fn(mlx_image_t *, uint32_t,
			uint32_t, t_start *start), t_start *start)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			fn(image, x, y, start);
			x++;
		}
		y++;
	}
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

// TODO create exit function
mlx_image_t	*new_image(t_vector size, t_vector origin)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = get_mlx();
	image = mlx_new_image(mlx, size.x, size.y);
	if (!image)
		exit (1);
	if (mlx_image_to_window(mlx, image, origin.x, origin.y) == -1)
		exit(1);
	return (image);
}

mlx_image_t	*new_image_full(void)
{
	t_vector	size;
	t_vector	origin;

	size.x = WIDTH;
	size.y = HEIGHT;
	origin.x = 0;
	origin.y = 0;
	return (new_image(size, origin));
}
