/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:53:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/12 21:26:26 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	else if (angle < 0)
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
		image = mlx_add_image(mlx, WIDTH, HEIGHT, (int[]){0, HEIGHT});
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
