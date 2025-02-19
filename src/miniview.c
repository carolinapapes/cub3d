/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:53:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/19 20:30:56 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
* @brief Gets the player's absolute position (center of the player);
*
* @return t_vector The player's position (x, y);
*/
t_vector	get_player_pos(void)
{
	mlx_image_t	*player_mlx;
	t_vector		player;

	player_mlx = get_player();
	player.x = PLAYER_SIZE / 2 + player_mlx->instances[0].x;
	player.y = PLAYER_SIZE / 2 + player_mlx->instances[0].y;
	return (player);
}

t_vector	get_quadrant(double angle)
{
	t_vector	quadrant;

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

double	get_grid_distance(t_vector player, int axis, int dir)
{
	if (dir == POSITIVE)
		return (ceil((player.arr[axis] + PLAYER_SIZE / 2) / GRID_SIZE)
			* GRID_SIZE);
	else if (dir == NEGATIVE)
		return (floor((player.arr[axis] - PLAYER_SIZE / 2) / GRID_SIZE)
			* GRID_SIZE);
	else
		return (player.arr[axis]);
}

void	get_dir_grid(mlx_image_t *image, int dir)
{
	t_vector	grid_distance;
	t_vector	player;
	t_vector	quadrant;
	double	angle;

	angle = get_angle(dir);
	quadrant = get_quadrant(angle);
	player = get_player_pos();
	grid_distance.x = get_grid_distance(player, X, quadrant.x);
	grid_distance.y = get_grid_distance(player, Y, quadrant.y);
	grid_distance.x -= image->instances[0].x;
	grid_distance.y -= image->instances[0].y;
	draw_cross(image, grid_distance);
}

/*
 * @brief Gets the next pixel of the ray coordinates for given axis
 *
 * In order to draw the ray we need to calculate the next pixel.
 *@param view The player's view
 *@param delta The player's delta
 *@param len The length of the ray
 *@param axis The axis to calculate the next pixel
 *@return The next pixel
 */
double	next_ray_pixel(t_vector view, t_vector delta, int len, int axis)
{
	double	pixel;

	pixel = round(view.arr[axis] + len * delta.arr[axis]);
	return (pixel);
}

/*
 * @brief Check if the pixel is new
 *
 * Because the math result of delta is not always an integer
 * we need to check if the pixel is new
 * to avoid drawing the same pixel multiple times
 * @param point The point to check
 * @param view The player's view
 * @param delta The player's delta
 * @param len The length of the ray
 */
int	is_new_pixel(t_vector *point, t_vector view, t_vector delta, int len)
{
	if (point->x != next_ray_pixel(view, delta, len, X)
		|| point->x != next_ray_pixel(view, delta, len, Y))
	{
		point->x = next_ray_pixel(view, delta, len, X);
		point->y = next_ray_pixel(view, delta, len, Y);
		return (1);
	}
	return (0);
}

void	fov_add_color(mlx_image_t *view_mlx, int dir)
{
	t_vector	endpoint;
	t_vector	player_pos_on_view_mlx;
	t_vector	point;
	int		len;

	len = 200;
	player_pos_on_view_mlx = get_pov(view_mlx);
	endpoint = get_ray_endpoint(dir, 1);
	point = player_pos_on_view_mlx;
	while (len--)
		if (is_new_pixel(&point, player_pos_on_view_mlx, endpoint, len))
			add_mlx_pixel(view_mlx, point, 0xFF0000FF);
}

mlx_image_t	*get_view(mlx_t *mlx)
{
	static mlx_image_t	*image;

	if (!image)
		image = mlx_add_image(mlx, WIDTH, HEIGHT, (int[]){0, 0});
	return (image);
}

void	view_rotate(int dir)
{
	mlx_image_t	*view_mlx;

	view_mlx = get_view(NULL);
	mlx_clear_image(view_mlx);
	fov_add_color(view_mlx, dir);
	get_dir_grid(view_mlx, dir);
}

void	view_move(t_vector movement)
{
	mlx_image_t	*view_mlx;

	view_mlx = get_view(NULL);
	view_mlx->instances[0].x += movement.x;
	view_mlx->instances[0].y += movement.y;
}
