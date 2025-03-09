/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:31 by capapes           #+#    #+#             */
/*   Updated: 2025/03/09 20:03:00 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

uint32_t	get_pixel_info(uint8_t *pixels, uint32_t index)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = pixels[index];
	g = pixels[index + 1];
	b = pixels[index + 2];
	a = pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

t_texture	*_get_texture(void)
{
	static t_texture	texture;

	return (&texture);
}

uint32_t	get_texture_color(void)
{
	uint32_t	color;
	uint32_t	pixel_index;
	t_texture	*texture;

	texture = _get_texture();
	pixel_index = texture->image[texture->ongoing]->width
		* (int)(texture->origin.y)
		+ (int)(texture->origin.x);
	pixel_index *= texture->image[texture->ongoing]->bytes_per_pixel;
	color = get_pixel_info(texture->image[texture->ongoing]->pixels, pixel_index);
	return (color);
}

mlx_texture_t	*load_texture(char *path)
{
	mlx_texture_t		*mlx_texture;

	mlx_texture = mlx_load_png(path);
	if (!mlx_texture)
		clean_exit(TERMINATE_MLX | FREE_START);
	return (mlx_texture);
}

void	load_texture_images(void)
{
	t_start		*start;
	t_texture	*texture;

	start = get_start();
	texture = _get_texture();
	texture->image[NORTH_TEXTURE] = load_texture(start->n_fd);
	texture->image[SOUTH_TEXTURE] = load_texture(start->s_fd);
	texture->image[WEST_TEXTURE] = load_texture(start->w_fd);
	texture->image[EAST_TEXTURE] = load_texture(start->e_fd);
}

t_texture	get_texture(void)
{
	t_texture	*texture;

	texture = _get_texture();
	return (*texture);
}

void	set_texture_x(double grid_intersection, double direction)
{
	double		x_percentage;
	t_texture	*texture;

	x_percentage = fmod(grid_intersection, GRID_SIZE) / GRID_SIZE;
	texture = _get_texture();
	texture->origin.y = 0;
	printf("direction: %f\n", direction);
	if (direction == POSITIVE)
		x_percentage = 1 - x_percentage;
	texture->origin.x = x_percentage
		* (double)(texture->image[texture->ongoing]->width);
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

	texture = _get_texture();
	ongoing = get_ongoing_texture(axis, quadrant);
	texture->ongoing = ongoing;
}

void	set_texture_step_y(double distance)
{
	t_texture	*texture;

	texture = _get_texture();
	texture->step.y = (double)texture->image[texture->ongoing]->height / distance;
}

int	add_to_texture_origin_y(void)
{
	t_texture	*texture;

	texture = _get_texture();
	texture->origin.y += texture->step.y;
	return (texture->origin.y < 0
		|| texture->origin.y >= texture->image[texture->ongoing]->height);
}
