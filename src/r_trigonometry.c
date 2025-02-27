/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_trigonometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:54:32 by capapes           #+#    #+#             */
/*   Updated: 2025/02/26 17:26:35 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// TAN = y / x;
// y = TAN * x;
// x = 1/TAN * y;
// Only for triangle rectangles
double	get_side_len(t_vector a1, t_vector a2, t_vector tan,
	t_axis axis)
{
	double	a_len;
	double	b_len;

	a_len = a1.arr[axis] - a2.arr[axis];
	b_len = a_len * tan.arr[axis];
	return (b_len);
}

double	get_hypot(t_vector a, t_vector b)
{
	return (hypot(b.x - a.x, b.y - a.y));
}
