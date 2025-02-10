/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:53:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/10 15:41:40 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>
#include <string.h>

#define M_PI 3.14159265358979323846

double	area(double *a, double *b, double *c)
{
	return (fabs((a[X] * (b[Y] - c[Y]) + b[X] * (c[Y] - a[Y]) + c[X] * (a[Y]
					- b[Y])) / 2));
}

double	area_t(t_triangle t)
{
	return (area(t.a, t.b, t.c));
}

double	is_point_inside_triangle(t_triangle t, double *p)
{
	double	a1;
	double	a2;
	double	a3;

	a1 = area(p, t.a, t.b);
	a2 = area(p, t.b, t.c);
	a3 = area(p, t.c, t.a);
	return (t.area == a1 + a2 + a3);
}

void	get_player_pos(double *pos)
{
	mlx_image_t	*player_mlx;

	player_mlx = get_player();
	pos[X] = player_mlx->instances[0].x;
	pos[Y] = player_mlx->instances[0].y - HEIGHT;
}

void	fov_add_color_iter(mlx_image_t *image, uint32_t x, uint32_t y)
{
	t_triangle	triangle_x;
	double		point[2];
	mlx_image_t	*player_mlx;

	point[X] = x;
	point[Y] = y;
	player_mlx = get_player();
	get_player_pos(triangle_x.c);
	triangle_x.a[X] = 0;
	triangle_x.a[Y] = floor(triangle_x.c[X] * tan(FOV / 2 * M_PI / 180));
	triangle_x.b[X] = 0;
	triangle_x.b[Y] = floor(triangle_x.c[Y] + triangle_x.c[Y] - triangle_x.a[Y]);
	triangle_x.area = area_t(triangle_x);
	if (is_point_inside_triangle(triangle_x, point))
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
	// cor[0][Y] = p3[X] * tan(FOV / 2);
	// cor[1][X] = p3[Y] * tan(90 - (FOV / 2));
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