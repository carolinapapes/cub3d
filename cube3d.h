/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:13 by capapes           #+#    #+#             */
/*   Updated: 2025/02/06 17:09:06 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "lib/MLX42.h"

# define WIDTH 512
# define HEIGHT 1027
# define WINDOW_TITLE "Cube3D"

# define WALL 1
# define ITEM 2
# define PLAYER 4
# define GRID 8

void	*add_minimap(mlx_image_t *image, uint32_t x, uint32_t y, void *param);
void	iter_image(mlx_image_t *image, void *(fn)(mlx_image_t *, uint32_t,
				uint32_t, void *), void *param);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

#endif