/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:31:42 by capapes           #+#    #+#             */
/*   Updated: 2025/03/12 20:17:12 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
		set_pixel(image, pixel, color);
	}
}

t_color	get_shadow_color(double distance)
{
	t_color	shadow_color;
	double	shadow_tint;

	if (distance >= HEIGHT)
		distance = HEIGHT - 1;
	shadow_tint = (double)distance / 4;
	shadow_color.r = shadow_tint;
	shadow_color.g = shadow_tint;
	shadow_color.b = shadow_tint;
	shadow_color.a = 50;
	return (shadow_color);
}

void	draw_line_render(t_vector origin, int len)
{
	mlx_image_t		*image;
	mlx_image_t		*shadow;
	t_color			shadow_color;

	image = get_render_image();
	shadow = get_shadow_image();
	shadow_color = get_shadow_color(len);
	set_texture_step_y(len);
	while (len--)
	{
		origin.y++;
		if (add_to_texture_origin_y())
			continue ;
		if (origin.x < 0 || origin.x >= WIDTH
			|| origin.y < 0 || origin.y >= HEIGHT)
			continue ;
		set_pixel(shadow, origin, shadow_color.rgba);
		set_pixel(image, origin, get_texture_color());
	}
}

// wall_start_x : x position in the render where the wall starts
void	draw_render(double distance, int window_x)
{
	int				strip_height;
	t_vector		origin;
	t_constants		constants;

	constants = game_constants();
	origin.x = window_x;
	strip_height = fabs(constants.strip_height / distance);
	origin.y = (HEIGHT - strip_height) / 2;
	draw_line_render(origin, strip_height);
}
