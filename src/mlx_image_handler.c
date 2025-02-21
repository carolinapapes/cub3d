/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:57:39 by capapes           #+#    #+#             */
/*   Updated: 2025/02/21 18:00:55 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// TODO create exit function
mlx_image_t	*new_image(t_vector size, t_vector origin)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = get_mlx();
	image = mlx_new_image(mlx, size.x, size.y);
	if (!image)
		exit (1);
	if (mlx_image_to_window(mlx, image, origin.x, origin.y) == -1)
		exit(1);
	return (image);
}

mlx_image_t	*new_image_full(void)
{
	t_vector	size;
	t_vector	origin;

	size.x = WIDTH;
	size.y = HEIGHT;
	origin.x = 0;
	origin.y = 0;
	return (new_image(size, origin));
}
