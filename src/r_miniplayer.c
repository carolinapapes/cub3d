/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_miniplayer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:57:55 by capapes           #+#    #+#             */
/*   Updated: 2025/03/12 16:58:00 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*init_miniplayer_image(void)
{
	t_constants		constants;
	mlx_image_t		*image;

	constants = game_constants();
	image = get_image(constants.player_size, constants.zero);
	set_pixels_color(image, HEX_PLAYER);
	return (image);
}

mlx_image_t	*get_miniplayer_image(void)
{
	static mlx_image_t	*image;

	if (!image)
		image = init_miniplayer_image();
	return (image);
}

mlx_image_t	*get_miniview_image(void)
{
	static mlx_image_t	*mlx_aux;

	if (!mlx_aux)
		mlx_aux = get_full_image();
	return (mlx_aux);
}
