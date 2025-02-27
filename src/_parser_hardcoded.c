/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser_hardcoded.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:19:41 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 19:14:47 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	player_init(t_start *start)
{
	t_vector	initial_pos;

	initial_pos.x = (start->player_pos.x + 0.25) * GRID_SIZE;
	initial_pos.y = (start->player_pos.y + 0.25) * GRID_SIZE;
	set_player(initial_pos, 0);
}
