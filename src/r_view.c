/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_view.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:53:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/25 23:24:12 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
