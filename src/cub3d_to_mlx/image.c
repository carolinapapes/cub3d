/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:09:57 by capapes           #+#    #+#             */
/*   Updated: 2025/03/13 14:39:16 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static mlx_image_t	*init_image(t_vector size)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = get_window();
	image = mlx_new_image(mlx, size.x, size.y);
	if (!image)
		clean_exit(TERMINATE_MLX | FREE_START);
	return (image);
}

static void	add_image(mlx_image_t *image, t_vector origin)
{
	mlx_t		*mlx;
	int			res;

	mlx = get_window();
	res = mlx_image_to_window(mlx, image, origin.x, origin.y);
	if (res == -1)
		clean_exit(TERMINATE_MLX | FREE_START);
}

mlx_image_t	*get_image(t_vector size, t_vector origin)
{
	mlx_image_t	*image;

	image = init_image(size);
	add_image(image, origin);
	return (image);
}

mlx_image_t	*get_image_full(void)
{
	t_constants	constants;
	mlx_image_t	*image;

	constants = game_constants();
	image = get_image(constants.window_size, constants.zero);
	return (image);
}

mlx_texture_t	*load_png(char *path)
{
	mlx_texture_t		*mlx_texture;

	mlx_texture = mlx_load_png(path);
	if (!mlx_texture)
		clean_exit(FREE_START);
	return (mlx_texture);
}
