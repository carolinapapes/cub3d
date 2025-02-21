/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _debug_fns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:21:22 by capapes           #+#    #+#             */
/*   Updated: 2025/02/21 19:12:47 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_player(void)
{
	t_player	*player;

	player = get_player();
	printf("----------------------------------------\n");
	printf("\t\tPlayer\n");
	printf("Pos: %f, %f\n", player->pos.x, player->pos.y);
	printf("Angle: %f\n", player->pov.angle);
	printf("Ratio: %f, %f\n", player->pov.t_ratio.x, player->pov.t_ratio.y);
	printf("Quad: %d, %d\n", player->pov.quadrant.x, player->pov.quadrant.y);
	printf("----------------------------------------\n");
}
