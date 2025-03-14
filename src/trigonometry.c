/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_trigonometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:54:32 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 05:12:59 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	get_side_len(t_vector next, t_vector end, t_vector tan,
	t_axis axis)
{
	return ((next.arr[axis] - end.arr[axis]) * tan.arr[axis]);
}

double	get_hypot(t_vector a, t_vector b)
{
	return (hypot(b.x - a.x, b.y - a.y));
}

double	radian_overflow(double angle)
{
	double	limit;

	limit = game_constants().double_pi;
	if (angle > limit)
		angle -= limit;
	if (angle < 0)
		angle += limit;
	return (angle);
}

t_vector	vector_sum(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}
