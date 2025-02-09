/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:53:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/09 20:09:50 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <string.h>
#include <math.h>

double	area(double *p1, double *p2, double *p3)
{
	return (fabs((p1[X] * (p2[Y] - p3[Y]) + p2[X] * (p3[Y] - p1[Y]) + p3[X]
				* (p1[Y] - p2[Y])) / 2));
}

double	is_point_inside_triangle(double *p1, double *p2, double *p3, double *p)
{
	double	a;
	double	a1;
	double	a2;
	double	a3;

	a = area(p1, p2, p3);
	a1 = area(p, p2, p3);
	a2 = area(p1, p, p3);
	a3 = area(p1, p2, p);
	return (a == a1 + a2 + a3);
}

void	fov_add_color_iter(mlx_image_t *image, uint32_t x, uint32_t y)
{
	double		p1[2];
	double		p2[2];
	double		p3[2];
	mlx_image_t	*player_mlx;

	p1[X] = 0;
	p1[Y] = 0;
	p2[X] = 0;
	p2[Y] = image->height;
	player_mlx = get_player();
	p3[X] = player_mlx->instances[0].x;
	p3[Y] = player_mlx->instances[0].y - HEIGHT;
	if (is_point_inside_triangle(p1, p2, p3, (double[2]){x, y}))
		mlx_put_pixel(image, x, y, FOV_COLOR);
}

mlx_image_t	*view_manager(mlx_t *mlx, int x, int y, int flag)
{
	static mlx_image_t	*image;

	if (flag != SET_PLAYER)
		return (image);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
		return (NULL);
	iter_image(image, fov_add_color_iter);
	x = x * GRID_SIZE + PLAYER_SIZE / 2 - WIDTH / 2;
	y = y * GRID_SIZE + PLAYER_SIZE / 2 - HEIGHT / 2;
	if (mlx_image_to_window(mlx, image, x, y + HEIGHT) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
	}
	return (image);
}

mlx_image_t	*get_view(void)
{
	return (view_manager(NULL, 0, 0, 0));
}

void	set_view(mlx_t *mlx, int x, int y)
{
	view_manager(mlx, x, y, SET_PLAYER);
}

// void	miniview_hook(int axis, int sign)
// {
// 	mlx_image_t *player_mlx;
// 	int movement_size;
// 	int player[2];
// 	double view_dir;

// 	view_dir = 1;
// 	player_mlx = get_view();
// 	player[X] = player_mlx->instances[0].x;
// 	player[Y] = player_mlx->instances[0].y - HEIGHT;
// 	view_dir =
// }