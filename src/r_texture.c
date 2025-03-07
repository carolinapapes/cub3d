/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:31 by capapes           #+#    #+#             */
/*   Updated: 2025/03/07 13:28:44 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

uint32_t	get_pixel_info(mlx_image_t *texture, uint32_t pixel_index)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = texture->pixels[pixel_index];
	g = texture->pixels[pixel_index + 1];
	b = texture->pixels[pixel_index + 2];
	a = texture->pixels[pixel_index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_texture_color(t_texture texture)
{
	uint32_t	color;
	uint32_t	pixel_index;

	pixel_index = texture.image->width * (int)(texture.origin.y)
		+ (int)(texture.origin.x);
	pixel_index *= 4;
	color = get_pixel_info(texture.image, pixel_index);
	return (color);
}

#define RESET_ORIGIN 1
#define SET_X 2

t_texture	handle_texture(int flag, double x_percentage)
{
	static t_texture	texture;
	mlx_texture_t		*mlx_texture;

	if (!texture.image)
	{
		mlx_texture = mlx_load_png("./textures/mario.png");
		if (!mlx_texture)
			exit(1);
		texture.image = mlx_texture_to_image(get_mlx(), mlx_texture);
		mlx_delete_texture(mlx_texture);
	}
	if (flag == RESET_ORIGIN)
	{
		texture.origin.x = 0;
		texture.origin.y = 0;
	}
	if (flag == SET_X)
		texture.origin.x = x_percentage * (double)(texture.image->width);
	return (texture);
}

t_texture	get_texture(void)
{
	return (handle_texture(0, 0));
}

void	set_texture_x(double grid_intersection)
{
	double	x_percentage;

	x_percentage = fmod(grid_intersection, GRID_SIZE) / GRID_SIZE;
	if (x_percentage < 0)
		x_percentage = 1 + x_percentage;
	handle_texture(SET_X, x_percentage);
}
