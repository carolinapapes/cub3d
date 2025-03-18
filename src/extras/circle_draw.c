/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:28 by capapes           #+#    #+#             */
/*   Updated: 2025/03/18 18:08:41 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	draw_octant(int x, int y, int mx, int my, mlx_image_t *image)
{
	mlx_put_pixel(image, mx + x, my + y, 0x000000FF);
	mlx_put_pixel(image, mx + x, my - y, 0x000000FF);
	mlx_put_pixel(image, mx - x, my + y, 0x000000FF);
	mlx_put_pixel(image, mx - x, my - y, 0x000000FF);
	mlx_put_pixel(image, mx + y, my + x, 0x000000FF);
	mlx_put_pixel(image, mx + y, my - x, 0x000000FF);
	mlx_put_pixel(image, mx - y, my + x, 0x000000FF);
	mlx_put_pixel(image, mx - y, my - x, 0x000000FF);
}

void	circle(int mx, int my, int r, mlx_image_t *image)
{
	int	t1;
	int	t2;
	int	x;
	int	y;

	t1 = r / 16;
	t2 = 0;
	x = r;
	y = 0;
	while (x >= y)
	{
		draw_octant(x, y, mx, my, image);
		y = y + 1;
		t1 = t1 + y;
		t2 = t1 - x;
		if (t2 >= 0)
		{
			t1 = t2;
			x = x - 1;
		}
	}
}
