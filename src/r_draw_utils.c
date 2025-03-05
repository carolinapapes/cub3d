/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:31:42 by capapes           #+#    #+#             */
/*   Updated: 2025/03/05 10:40:20 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_pixel(mlx_image_t *image, t_vector pixel, int32_t color)
{
	mlx_put_pixel(image, pixel.x, pixel.y, color);
}

void	draw_point(t_vector point, int color)
{
	int			width;
	int			height;
	int			x;
	int			y;
	mlx_image_t	*aux;

	aux = get_miniview_image();
	if (point.x < 0 || point.x >= WIDTH || point.y < 0 || point.y >= HEIGHT)
		return ;
	width = 5;
	while (width-- > -5)
	{
		height = 5;
		while (height-- > -5)
		{
			x = point.x + width;
			y = point.y + height;
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
				mlx_put_pixel(aux, x, y, color);
		}
	}
}

// TODO: check if mlx add pixel is needed
void	draw_line(t_vector origin, t_vector direction, int len, int color)
{
	t_vector	pixel;
	mlx_image_t	*image;

	image = get_miniview_image();
	len = abs(len);
	if (len < 0)
		return ;
	while (len--)
	{
		pixel.x = origin.x + direction.x * len;
		pixel.y = origin.y + direction.y * len;
		if (pixel.x < 0 || pixel.x >= WIDTH || pixel.y < 0 || pixel.y >= HEIGHT)
			continue ;
		draw_pixel(image, pixel, color);
	}
}
uint32_t	get_pixel_info(mlx_image_t *texture, uint16_t pixel_index)
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

t_color get_shadow_color(double distance)
{
	t_color	shadow_color;
	double	shadow_tint;

	shadow_tint = (double)distance / 4;
	shadow_color.r = shadow_tint;
	shadow_color.g = shadow_tint;
	shadow_color.b = shadow_tint;
	shadow_color.a = 100;
	return (shadow_color);
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

void	draw_line_render(t_vector origin, t_vector direction,
		int height_len, t_texture texture)
{
	t_vector		pixel;
	mlx_image_t		*image;
	mlx_image_t		*shadow;
	t_color			shadow_color;

	image = get_render_image();
	shadow = get_shadow_image();
	shadow_color = get_shadow_color(height_len);
	while (height_len--)
	{
		pixel.x = origin.x + direction.x * height_len;
		pixel.y = origin.y + direction.y * height_len;
		texture.origin.y -= texture.step.y;
		if (pixel.x < 0 || pixel.x >= WIDTH || pixel.y < 0 || pixel.y >= HEIGHT)
		continue ;
		draw_pixel(image, pixel, get_texture_color(texture));
		draw_pixel(shadow, pixel, shadow_color.rgba);
	}
}

// wall_start_x : x position in the render where the wall starts
void	draw_render(double distance, int iter)
{
	int				strip_height;
	int				end;
	t_vector		wall_start;
	t_constants		constants;
	t_texture		texture;
	
	constants = game_constants();
	wall_start.x = (iter - 1) * constants.strip_width;
	end = wall_start.x + constants.strip_width;
	strip_height = fabs(constants.strip_height / distance);
	wall_start.y = (HEIGHT - strip_height) / 2;
	texture = get_texture(0, 0, 0);
	texture.step.y = (double)texture.image->height / strip_height;
	while (wall_start.x++ < end && wall_start.x < WIDTH)
	{
		texture.origin.x += texture.step.x;
		if (texture.origin.x >= texture.image->width)
			texture.origin.x = fmod(texture.step.x, 1024);
		printf("Y = %.2f | x %.2f\n", texture.origin.y, texture.origin.x);
		draw_line_render(wall_start, constants.dir_y, strip_height, texture);
	}
}
