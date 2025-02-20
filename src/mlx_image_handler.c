/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:57:39 by capapes           #+#    #+#             */
/*   Updated: 2025/02/20 17:12:07 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// TODO create exit function
mlx_image_t	*new_image(t_vector size, t_vector origin)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_handler();
	image = mlx_new_image(mlx, size.x, size.y);
	if (!image)
		exit (1);
	if (mlx_image_to_window(mlx, image, origin.x, origin.y) == -1)
		exit(1);
	return (image);
}

mlx_image_t	*new_image_full(void)
{
	return (new_image((t_vector){WIDTH, HEIGHT}, (t_vector){0, 0}));
}
