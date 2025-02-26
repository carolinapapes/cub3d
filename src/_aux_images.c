/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _aux_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:03:16 by capapes           #+#    #+#             */
/*   Updated: 2025/02/26 15:14:47 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*init_player_image(void)
{
	t_vector	size;
	t_vector	origin;
	mlx_image_t	*image;

	origin.x = 0;
	origin.y = 0;
	size.x = PLAYER_SIZE;
	size.y = PLAYER_SIZE;
	image = new_image(size, origin);
	image_full_color(image, PLAYER_COLOR);
	return (image);
}

void	update_mlx_player(t_player *player)
{
	player->mlx_player->instances[0].x = player->pos.x;
	player->mlx_player->instances[0].y = player->pos.y;
}

mlx_image_t	*get_view(void)
{
	static mlx_image_t	*mlx_view;

	if (!mlx_view)
		mlx_view = new_image_full();
	return (mlx_view);
}

mlx_image_t	*get_render(void)
{
	static mlx_image_t	*mlx_render;

	if (!mlx_render)
		mlx_render = new_image_full();
	return (mlx_render);
}

mlx_image_t	*get_aux(void)
{
	static mlx_image_t	*mlx_aux;

	if (!mlx_aux)
		mlx_aux = new_image_full();
	return (mlx_aux);
}
