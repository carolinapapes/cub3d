/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:53:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/14 13:33:56 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_coord	get_player_pos(void)
{
	mlx_image_t	*player_mlx;
	t_coord		player;

	player_mlx = get_player();
	player.x = PLAYER_SIZE / 2 + player_mlx->instances[0].x;
	player.y = PLAYER_SIZE / 2 + player_mlx->instances[0].y - HEIGHT;
	return (player);
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

t_coord	get_delta(double angle)
{
	t_coord	delta;

	delta.x = cos(angle * M_PI);
	delta.y = sin(angle * M_PI);
	return (delta);
}

t_coord	get_point(mlx_image_t *image)
{
	t_coord	point;

	point = get_player_pos();
	point.x -= image->instances[0].x;
	point.y -= image->instances[0].y - HEIGHT;
	return (point);
}

void	fov_add_color(mlx_image_t *image, int dir)
{
	double	angle;
	t_coord	delta;
	t_coord	point;
	int		len;

	len = 100;
	point = get_point(image);
	angle = get_angle(dir);
	delta = get_delta(angle);
	while (len--)
	{
		mlx_put_pixel(image, point.x + (len + 10) * delta.x, point.y
			+ delta.y * (len + 10), 0xFF0000FF);
	}
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

void	view_move(t_coord movement)
{
	mlx_image_t	*view_mlx;

	view_mlx = get_view(NULL);
	view_mlx->instances[0].x += movement.x;
	view_mlx->instances[0].y += movement.y;
}
