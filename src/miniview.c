/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:53:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/20 19:05:16 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_vector	get_quadrant(double angle)
{
	t_vector	quadrant;
	double		angle;

	angle = get_angle(0);
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

double	get_grid_distance(int axis, int quadrant)
{
	t_vector	player;

	player = get_player_pos();
	if (quadrant == POSITIVE)
		return (ceil((player.arr[axis] + PLAYER_SIZE / 2) / GRID_SIZE)
			* GRID_SIZE);
	else if (quadrant == NEGATIVE)
		return (floor((player.arr[axis] - PLAYER_SIZE / 2) / GRID_SIZE)
			* GRID_SIZE);
	else
		return (player.arr[axis]);
}

void	set_view(void)
{
	static mlx_image_t	*image;
	t_player			player;
	t_vector			grid_distance;
	t_vector			quadrant;

	if (!image)
		image = new_image_full();
	mlx_clear_image(image);
	draw_line(image, player.pos, player.pov, 100);
	quadrant = get_quadrant(player.pov_a);
	grid_distance.x = get_grid_distance(X, quadrant.x);
	grid_distance.y = get_grid_distance(Y, quadrant.y);
	draw_cross(image, grid_distance);
	return (image);
}
