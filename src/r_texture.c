/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:31 by capapes           #+#    #+#             */
/*   Updated: 2025/03/13 20:23:15 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_texture	*get_texture(void)
{
	static t_texture	texture;

	return (&texture);
}

mlx_texture_t	*get_ongoing_texture(int axis, int quadrant)
{
	t_constants	constants;
	int			res;

	constants = game_constants();
	if (axis == X && quadrant < 0)
		res = NORTH_TEXTURE;
	else if (axis == X && quadrant > 0)
		res = SOUTH_TEXTURE;
	else if (quadrant > 0)
		res = EAST_TEXTURE;
	else
		res = WEST_TEXTURE;
	return (constants.textures[res]);
}

void	set_ongoing_wall_texture(int axis, int quadrant)
{
	mlx_texture_t	*ongoing;
	t_texture		*texture;

	texture = get_texture();
	ongoing = get_ongoing_texture(axis, quadrant);
	texture->image = ongoing;
}

void	set_texture_x(double grid_intersection, double direction)
{
	double		x_percentage;
	t_texture	*texture;

	x_percentage = fmod(grid_intersection, GRID_SIZE) / GRID_SIZE;
	texture = get_texture();
	texture->origin.y = 0;
	if (direction == POSITIVE)
		x_percentage = 1 - x_percentage;
	texture->origin.x = x_percentage * texture->image->width;
}

void	set_texture_step_y(double distance)
{
	t_texture	*texture;

	texture = get_texture();
	texture->step.y = (double)texture->image->height / distance;
}

int	add_to_texture_origin_y(void)
{
	t_texture	*texture;

	texture = get_texture();
	texture->origin.y += texture->step.y;
	return (texture->origin.y < 0
		|| texture->origin.y >= texture->image->height);
}

uint32_t	get_texture_color(void)
{
	uint32_t		color;
	uint32_t		px_index;
	t_texture		*texture;

	texture = get_texture();
	px_index = texture->image->width * (int)(texture->origin.y)
		+ (int)(texture->origin.x);
	px_index *= texture->image->bytes_per_pixel;
	color = get_pixel(texture->image->pixels, px_index);
	return (color);
}

t_vector	vector_sum(t_vector a, t_vector b)
{
	t_vector res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}
