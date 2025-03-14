/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:57:55 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 13:15:44 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static mlx_image_t	*init_miniplayer(void)
{
	t_constants		constants;
	mlx_image_t		*image;

	constants = game_constants();
	image = get_image(constants.player_size, constants.zero);
	set_pixels(image, HEX_PLAYER);
	return (image);
}

mlx_image_t	*get_miniplayer(void)
{
	static mlx_image_t	*image;

	if (!image)
		image = init_miniplayer();
	return (image);
}

mlx_image_t	*get_miniview(void)
{
	static mlx_image_t	*mlx_aux;

	if (!mlx_aux)
		mlx_aux = get_image_full();
	return (mlx_aux);
}
