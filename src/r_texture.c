/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:31 by capapes           #+#    #+#             */
/*   Updated: 2025/03/12 20:54:32 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_texture	*set_texture(void)
{
	static t_texture	texture;

	return (&texture);
}

void	load_texture_images(void)
{
	t_start		*start;
	t_texture	*texture;

	start = get_start();
	texture = set_texture();
	texture->image[NORTH_TEXTURE] = load_texture(start->n_fd);
	texture->image[SOUTH_TEXTURE] = load_texture(start->s_fd);
	texture->image[WEST_TEXTURE] = load_texture(start->w_fd);
	texture->image[EAST_TEXTURE] = load_texture(start->e_fd);
}

int	get_ongoing_texture(int axis, int quadrant)
{
	if (axis == X && quadrant < 0)
		return (NORTH_TEXTURE);
	if (axis == X && quadrant > 0)
		return (SOUTH_TEXTURE);
	if (quadrant > 0)
		return (EAST_TEXTURE);
	return (WEST_TEXTURE);
}

void	set_ongoing_wall_texture(int axis, int quadrant)
{
	int			ongoing;
	t_texture	*texture;

	texture = set_texture();
	ongoing = get_ongoing_texture(axis, quadrant);
	texture->ongoing = ongoing;
}

t_texture	get_texture(void)
{
	t_texture	*texture;

	texture = set_texture();
	return (*texture);
}

void	set_texture_x(double grid_intersection, double direction)
{
	double		x_percentage;
	t_texture	*texture;

	x_percentage = fmod(grid_intersection, GRID_SIZE) / GRID_SIZE;
	texture = set_texture();
	texture->origin.y = 0;
	if (direction == POSITIVE)
		x_percentage = 1 - x_percentage;
	texture->origin.x = x_percentage * texture->image[texture->ongoing]->width;
}

void	set_texture_step_y(double distance)
{
	t_texture	*texture;

	texture = set_texture();
	texture->step.y = (double)texture->image[texture->ongoing]->height
		/ distance;
}

int	add_to_texture_origin_y(void)
{
	t_texture	*texture;

	texture = set_texture();
	texture->origin.y += texture->step.y;
	return (texture->origin.y < 0
		|| texture->origin.y >= texture->image[texture->ongoing]->height);
}

uint32_t	get_texture_color(void)
{
	uint32_t		color;
	uint32_t		pixel_index;
	t_texture		texture;
	mlx_texture_t	*mlx_texture;

	texture = get_texture();
	mlx_texture = texture.image[texture.ongoing];
	pixel_index = mlx_texture->width * (int)(texture.origin.y)
		+ (int)(texture.origin.x);
	pixel_index *= mlx_texture->bytes_per_pixel;
	color = get_pixel(mlx_texture->pixels, pixel_index);
	return (color);
}
