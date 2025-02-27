/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser_hardcoded.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:19:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/21 19:11:45 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	player_init(void)
{
	t_vector	initial_pos;

	initial_pos.x = 5.25 * GRID_SIZE;
	initial_pos.y = 5.25 * GRID_SIZE;
	set_player(initial_pos, 0);
}
