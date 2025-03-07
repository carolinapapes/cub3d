/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:31 by capapes           #+#    #+#             */
/*   Updated: 2025/03/07 16:43:17 by capapes          ###   ########.fr       */
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

#define RESET_ORIGIN 1
#define SET_X 2
#define SET_TEXTURE 4
#define NORTH_TEXTURE 0
#define SOUTH_TEXTURE 1
#define WEST_TEXTURE 2
#define EAST_TEXTURE 3

t_texture	handle_texture(int flag, double x_percentage, int axis, int quadrant)
{
	static t_texture	texture;
	mlx_texture_t		*mlx_texture[4];
	t_start				*start;

	if (!texture.image[0])
	{
		start = get_start();
		mlx_texture[NORTH_TEXTURE] = mlx_load_png(start->n_fd);
		if (!mlx_texture[NORTH_TEXTURE])
			clean_exit(TERMINATE_MLX | FREE_START);
		texture.image[NORTH_TEXTURE] = mlx_texture[NORTH_TEXTURE];
		mlx_texture[SOUTH_TEXTURE] = mlx_load_png(start->s_fd);
		if (!mlx_texture[SOUTH_TEXTURE])
			clean_exit(TERMINATE_MLX | FREE_START);
		texture.image[SOUTH_TEXTURE] = mlx_texture[SOUTH_TEXTURE];
		mlx_texture[WEST_TEXTURE] = mlx_load_png(start->w_fd);
		if (!mlx_texture[WEST_TEXTURE])
			clean_exit(TERMINATE_MLX | FREE_START);
		texture.image[WEST_TEXTURE] = mlx_texture[WEST_TEXTURE];
		mlx_texture[EAST_TEXTURE] = mlx_load_png(start->e_fd);
		if (!mlx_texture[EAST_TEXTURE])
			clean_exit(TERMINATE_MLX | FREE_START);
		texture.image[EAST_TEXTURE] = mlx_texture[EAST_TEXTURE];
	}
	if (flag & SET_TEXTURE)
	{
		if (axis == X && quadrant < 0)
			texture.ongoing = NORTH_TEXTURE;
		else if (axis == X && quadrant > 0)
			texture.ongoing = SOUTH_TEXTURE;
		else if (quadrant > 0)
			texture.ongoing = EAST_TEXTURE;
		else
			texture.ongoing = WEST_TEXTURE;
	}
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
	return (handle_texture(0, 0, 0, 0));
}

void	set_texture_x(double grid_intersection)
{
	double	x_percentage;

	x_percentage = fmod(grid_intersection, GRID_SIZE) / GRID_SIZE;
	handle_texture(SET_X, x_percentage, 0, 0);
}

void	set_ongoing_view_wall(int axis, int quadrant)
{
	handle_texture(SET_TEXTURE, 0, axis, quadrant);
}
