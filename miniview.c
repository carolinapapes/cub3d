/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:53:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/11 23:48:13 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>
#include <string.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

void	get_player_pos(double *pos)
{
	mlx_image_t	*player_mlx;

	player_mlx = get_player();
	pos[X] = PLAYER_SIZE / 2 + player_mlx->instances[0].x;
	pos[Y] = PLAYER_SIZE / 2 + player_mlx->instances[0].y - HEIGHT;
}

// Returns the player's angle in radians
double	get_angle(int dir)
{
	static double	angle;

	if (!angle)
		angle = 0;
	if (dir == 1)
		angle += 0.01;
	else if (dir == -1)
		angle -= 0.01;
	if (angle > 2)
		angle = 0;
	if (angle < 0)
		angle = 2;
	return (angle);
}

void	fov_add_color(mlx_image_t *image, int dir)
{
	double	angle;
	double	delta[2];
	double	point[2];
	int		len;

	len = 100;
	get_player_pos(point);
	point[X] -= image->instances[0].x;
	point[Y] -= image->instances[0].y - HEIGHT;
	angle = get_angle(dir);
	delta[X] = cos(angle * M_PI);
	delta[Y] = sin(angle * M_PI);
	while (len--)
		mlx_put_pixel(image, point[X] + (len + 10) * delta[X], point[Y]
			+ delta[Y] * (len + 10), 0xFF0000FF);
}

mlx_image_t	*get_view(mlx_t *mlx)
{
	static mlx_image_t	*image;

	if (!image)
		image = mlx_add_image(mlx, WIDTH, HEIGHT);
	return (image);
}

void	view_rotate(int dir)
{
	mlx_image_t	*view_mlx;

	view_mlx = get_view(NULL);
	mlx_clear_image(view_mlx);
	fov_add_color(view_mlx, dir);
}

void	view_move(int x, int y)
{
	mlx_image_t	*view_mlx;

	view_mlx = get_view(NULL);
	view_mlx->instances[0].x += x;
	view_mlx->instances[0].y += y;
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

// OLD FN
// int	_fov_add_color_iter(mlx_image_t *image, uint32_t x, uint32_t y)
// {
// 	t_triangle	triangle_x;
// 	double		point[2];
// 	mlx_image_t	*player_mlx;

// 	triangle_x.a[X] = 0;
// 	triangle_x.a[Y] = floor(triangle_x.c[X] * tan(FOV / 2 * M_PI / 180));
// 	triangle_x.b[X] = 0;
// 	triangle_x.b[Y] = floor(triangle_x.c[Y] + triangle_x.c[Y]
// 			- triangle_x.a[Y]);
// 	triangle_x.area = area_t(triangle_x);
// 	if (is_point_inside_triangle(triangle_x, point))
// 		mlx_put_pixel(image, x, y, FOV_COLOR);
// }

// double	area(double *a, double *b, double *c)
// {
// 	return (fabs((a[X] * (b[Y] - c[Y]) + b[X] * (c[Y] - a[Y]) + c[X] * (a[Y]
// 					- b[Y])) / 2));
// }

// double	area_t(t_triangle t)
// {
// 	return (area(t.a, t.b, t.c));
// }

// double	is_point_inside_triangle(t_triangle t, double *p)
// {
// 	double	a1;
// 	double	a2;
// 	double	a3;

// 	a1 = area(p, t.a, t.b);
// 	a2 = area(p, t.b, t.c);
// 	a3 = area(p, t.c, t.a);
// 	return (t.area == a1 + a2 + a3);
// }
