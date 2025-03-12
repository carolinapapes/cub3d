/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_pixels.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:57:39 by capapes           #+#    #+#             */
/*   Updated: 2025/03/12 16:12:43 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_pixels_color(mlx_image_t *image, int32_t color)
{
	memset(image->pixels, color, image->width * image->height
		* sizeof(int32_t));
}

void	clear_pixels(mlx_image_t *image)
{
	set_pixels_color(image, 0x00000000);
}
