/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:31:42 by capapes           #+#    #+#             */
/*   Updated: 2025/02/26 12:20:45 by capapes          ###   ########.fr       */
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

	aux = get_aux();
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

	image = get_aux();
	len = abs(len);
	if (len < 0)
		return ;
	while (len--)
	{
		pixel.x = origin.x + direction.x * len;
		pixel.y = origin.y + direction.y * len;
		if (pixel.x < 0 || pixel.x >= WIDTH || pixel.y < 0 || pixel.y >= HEIGHT)
			break ;
		draw_pixel(image, pixel, color);
	}
}

void	draw_axis_line(int position, int axis)
{
	t_vector	pixel;
	int			len;
	mlx_image_t	*image;

	len = WIDTH;
	image = get_view();
	while (len--)
	{
		pixel.arr[axis] = position;
		pixel.arr[!axis] = len;
		draw_pixel(image, pixel, HEX_PURPLE - 0x00000088);
	}
}

void	draw_intersect(t_player player, t_vector next, int color)
{
	int			len;
	t_vector	origin;

	origin = get_player_pos(PIXEL | CENTER);
	len = abs((int)hypot(next.x - origin.x, next.y - origin.y));
	draw_line(origin, player.pov.t_ratio, len, color);
	draw_point(next, color);
}

void	draw_intersect_2(t_vector_full vector, int color)
{
	printf("origin: %f, %f\n", vector.origin.x, vector.origin.y);
	printf("end: %f, %f\n", vector.end.x, vector.end.y);
	printf("direction: %f, %f\n", vector.direction.x, vector.direction.y);
	printf("distance: %f\n", vector.distance);
	draw_line(vector.origin, vector.direction, vector.distance, color);
	draw_point(vector.end, color);
}
