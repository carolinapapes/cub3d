/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:31:42 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 12:27:38 by capapes          ###   ########.fr       */
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

	aux = get_miniview();
	if (point.x < 0 || point.x >= WINDOW_SIZE || point.y < 0
		|| point.y >= WINDOW_SIZE)
		return ;
	width = 5;
	while (width-- > -5)
	{
		height = 5;
		while (height-- > -5)
		{
			x = point.x + width;
			y = point.y + height;
			if (x >= 0 && x < WINDOW_SIZE && y >= 0 && y < WINDOW_SIZE)
				mlx_put_pixel(aux, x, y, color);
		}
	}
}

void	draw_line(t_vector origin, t_vector direction, int len, int color)
{
	t_vector	pixel;
	mlx_image_t	*image;

	image = get_miniview();
	len = abs(len);
	if (len < 0)
		return ;
	while (len--)
	{
		pixel.x = origin.x + direction.x * len;
		pixel.y = origin.y + direction.y * len;
		if (pixel.x < 0 || pixel.x >= WINDOW_SIZE || pixel.y < 0
			|| pixel.y >= WINDOW_SIZE)
			continue ;
		set_pixel(image, pixel, color);
	}
}

t_color	get_shadow_color(double distance)
{
	t_color	shadow_color;
	double	shadow_tint;

	if (distance >= WINDOW_SIZE)
		distance = WINDOW_SIZE - 1;
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
	double			step;

	image = get_render();
	shadow = get_shadow();
	shadow_color = get_shadow_color(len);
	step = (double)get_texture()->image->height / len;
	while (len--)
	{
		origin.y++;
		if (set_texture_y(step))
			continue ;
		if (origin.x < 0 || origin.x >= WINDOW_SIZE
			|| origin.y < 0 || origin.y >= WINDOW_SIZE)
			continue ;
		set_pixel(shadow, origin, shadow_color.rgba);
		set_pixel(image, origin, get_texture_color());
	}
}

void	draw_render(double distance, int window_x)
{
	int				strip_height;
	t_vector		origin;
	t_constants		constants;

	constants = game_constants();
	origin.x = window_x;
	strip_height = fabs(constants.strip_height / distance);
	origin.y = (WINDOW_SIZE - strip_height) / 2;
	draw_line_render(origin, strip_height);
}
