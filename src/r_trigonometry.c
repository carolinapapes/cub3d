/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_trigonometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:54:32 by capapes           #+#    #+#             */
/*   Updated: 2025/03/11 19:01:52 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// TAN = y / x;
// y = TAN * x;
// x = 1/TAN * y;
// Only for triangle rectangles
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

double	tends_to_zero(double x)
{
	double	eps;

	eps = 0.001;
	if (fabs(x) < eps)
		return (0.0);
	return (x);
}
