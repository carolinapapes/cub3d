/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_draw_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:31:42 by capapes           #+#    #+#             */
/*   Updated: 2025/02/25 20:18:37 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_pixel(mlx_image_t *image, t_vector pixel, int32_t color)
{
	mlx_put_pixel(image, pixel.x, pixel.y, color);
}

void	draw_point(mlx_image_t *image, t_vector point, int color)
{
	int	width;
	int	height;
	int	x;
	int	y;

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
				mlx_put_pixel(image, x, y, color);
		}
	}
}

// TODO: check if mlx add pixel is needed
// for each increment of length in draw_line
void	draw_line(mlx_image_t *image, t_vector origin, t_vector direction,
		int len, int color)
{
	t_vector	pixel;

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

void	draw_intersect(t_player player, t_vector next,
	int color)
{
	int			len;
	t_vector	origin;

	origin = get_player_pos(PIXEL | CENTER);
	len = (int)hypot(next.x - origin.x, next.y - origin.y);
	draw_line(player.mlx_view, origin, player.pov.t_ratio, len, color);
	draw_point(player.mlx_view, next, color);
}
