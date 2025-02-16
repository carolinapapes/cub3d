/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:53:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/16 20:33:34 by capapes          ###   ########.fr       */
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

t_coord	get_pov(mlx_image_t *image)
{
	t_coord	view;

	view = get_player_pos();
	view.x -= image->instances[0].x;
	view.y -= image->instances[0].y - HEIGHT;
	return (view);
}

void	draw_cross(mlx_image_t *image, t_coord point)
{
	int	offset;

	offset = 5;
	while (offset--)
	mlx_put_pixel(image, point.x + offset, point.y, 0x00FF00FF);
	while (offset++ < 5)
	mlx_put_pixel(image, point.x, point.y + offset, 0x00FF00FF);
}

t_coord	get_quadrant(double angle)
{
	t_coord	quadrant;

	quadrant.x = 0;
	quadrant.y = 0;
	if (angle > 0 && angle < 1)
		quadrant.y = POSITIVE;
	else if (angle > 1 && angle < 2)
		quadrant.y = NEGATIVE;
	if (angle > 0.5 && angle < 1.5)
		quadrant.x = NEGATIVE;
	else if ((angle > 1.5 && angle < 2) || (angle > 0 && angle < 0.5))
		quadrant.x = POSITIVE;
	return (quadrant);
}

double	get_grid_distance(t_coord player, int axis, int dir)
{
	if (dir == POSITIVE)
		return(ceil((player.arr[axis] + PLAYER_SIZE / 2) / GRID_SIZE) * GRID_SIZE);
	else if (dir == NEGATIVE)
		return(floor((player.arr[axis] - PLAYER_SIZE / 2) / GRID_SIZE) * GRID_SIZE);
	else 
		return (player.arr[axis]);
}

void	get_dir_grid(mlx_image_t *image, double angle)
{
	t_coord	grid_distance;
	t_coord	player;
	t_coord	quadrant;

	quadrant = get_quadrant(angle);
	player = get_player_pos();
	grid_distance.x = get_grid_distance(player, X, quadrant.x);
	grid_distance.y = get_grid_distance(player, Y, quadrant.y);
	grid_distance.x -= image->instances[0].x;
	grid_distance.y -= (image->instances[0].y - HEIGHT);
	draw_cross(image, grid_distance);
}

void	fov_add_color(mlx_image_t *image, int dir)
{
	double	angle;
	t_coord	delta;
	t_coord	view;
	int		len;

	len = 100;
	view = get_pov(image);
	angle = get_angle(dir);
	delta = get_delta(angle);
	while (len--)
	{
		mlx_put_pixel(image, view.x + (len + 10) * delta.x, view.y
			+ delta.y * (len + 10), 0xFF0000FF);
	}
	get_dir_grid(image, angle);
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
