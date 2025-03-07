/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:31 by capapes           #+#    #+#             */
/*   Updated: 2025/03/07 17:41:39 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

uint32_t	get_pixel_info(mlx_texture_t *texture, uint32_t pixel_index)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = texture->pixels[pixel_index];
	g = texture->pixels[pixel_index + 1];
	b = texture->pixels[pixel_index + 2];
	a = texture->pixels[pixel_index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_texture_color(t_texture texture)
{
	uint32_t	color;
	uint32_t	pixel_index;

	pixel_index = texture.image[texture.ongoing]->width
		* (int)(texture.origin.y)
		+ (int)(texture.origin.x);
	pixel_index *= 4;
	color = get_pixel_info(texture.image[texture.ongoing], pixel_index);
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

t_texture	handle_texture(int flag, double x_percentage, int ongoing)
{
	static t_texture	texture;
	t_start				*start;

	if (!texture.image[0])
	{
		start = get_start();
		texture.image[NORTH_TEXTURE] = load_texture(start->n_fd);
		texture.image[SOUTH_TEXTURE] = load_texture(start->s_fd);
		texture.image[WEST_TEXTURE] = load_texture(start->w_fd);
		texture.image[EAST_TEXTURE] = load_texture(start->e_fd);
	}
	if (flag & SET_TEXTURE)
		texture.ongoing = ongoing;
	if (flag & SET_X)
	{
		texture.origin.y = 0;
		texture.origin.x = x_percentage
			* (double)(texture.image[texture.ongoing]->width);
	}
	return (texture);
}

t_texture	get_texture(void)
{
	return (handle_texture(0, 0, 0));
}

void	set_texture_x(double grid_intersection)
{
	double	x_percentage;

	x_percentage = fmod(grid_intersection, GRID_SIZE) / GRID_SIZE;
	handle_texture(SET_X, x_percentage, 0);
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
	int	ongoing;

	ongoing = get_ongoing_texture(axis, quadrant);
	handle_texture(SET_TEXTURE, 0, ongoing);
}
