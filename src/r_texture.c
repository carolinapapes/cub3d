/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:31 by capapes           #+#    #+#             */
/*   Updated: 2025/03/05 19:02:49 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

uint32_t	get_pixel_info(mlx_image_t *texture, uint16_t pixel_index)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	// uint8_t	a;

	r = texture->pixels[pixel_index - 1];
	g = texture->pixels[pixel_index];
	b = texture->pixels[pixel_index + 1];
	// a = texture->pixels[pixel_index + 3];
	return (r << 24 | g << 16 | b << 8 | 255);
}

uint32_t	get_texture_color(t_texture texture)
{
	uint32_t	color;
	uint32_t	pixel_index;

	pixel_index = texture.image->width * (int)(texture.origin.y)
		+ (int)(texture.origin.x);
	if (pixel_index >= texture.image->width * texture.image->height)
		pixel_index = texture.image->width * texture.image->height - 1;
	color = get_pixel_info(texture.image, pixel_index);
	return (color);
}

t_texture	get_texture(int set, double origin_axis_pixel)
{
	static t_texture	texture;
	mlx_texture_t		*mlx_texture;

	if (!texture.image)
	{
		mlx_texture = mlx_load_png("./textures/rojo.png");
		if (!mlx_texture)
			exit(1);
		texture.image = mlx_texture_to_image(get_mlx(), mlx_texture);
	}
	if (set)
	{
		origin_axis_pixel = fmod(origin_axis_pixel,
				GRID_SIZE) / GRID_SIZE;
		texture.origin.y = 0;
		texture.origin.x = origin_axis_pixel * (double)(texture.image->width);
	}
	return (texture);
}
