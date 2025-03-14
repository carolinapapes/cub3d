/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:31 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 14:20:14 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

t_texture	*get_texture(void)
{
	static t_texture	texture;

	return (&texture);
}

void	set_texture_image(int axis, int quadrant)
{
	t_texture		*texture;
	t_constants		constants;
	int				res;

	texture = get_texture();
	constants = game_constants();
	if (axis == X && quadrant < 0)
		res = NORTH_TEXTURE;
	else if (axis == X && quadrant > 0)
		res = SOUTH_TEXTURE;
	else if (quadrant > 0)
		res = EAST_TEXTURE;
	else
		res = WEST_TEXTURE;
	texture->image = constants.textures[res];
}

void	set_texture_x(double grid_intersection, double direction, int axis)
{
	double		x_percentage;
	t_texture	*texture;

	x_percentage = fmod(grid_intersection, GRID_SIZE) / GRID_SIZE;
	texture = get_texture();
	texture->origin.y = 0;
	if (axis == X && direction == NEGATIVE)
		x_percentage = 1 - x_percentage;
	texture->origin.x = x_percentage * texture->image->width;
}

int	set_texture_y(double step)
{
	t_texture	*texture;

	texture = get_texture();
	texture->origin.y += step;
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
