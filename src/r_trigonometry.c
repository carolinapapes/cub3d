/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_trigonometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:54:32 by capapes           #+#    #+#             */
/*   Updated: 2025/03/13 20:48:14 by capapes          ###   ########.fr       */
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

void	generic_matrix_iter(t_vector constrains, void fn(t_vector))
{
	t_vector	coord;

	coord.y = 0;
	while (coord.y < constrains.y)
	{
		coord.x = 0;
		while (coord.x < constrains.x)
		{
			fn(coord);
			coord.x++;
		}
		coord.y++;
	}
}

void	set_timeout(void (*fn)(void), int delay)
{
	static t_timeval	last_time;
	t_timeval			current_time;
	int					elapsed_milliseconds;

	gettimeofday(&current_time, NULL);
	if (!last_time.tv_sec)
		last_time = current_time;
	elapsed_milliseconds = (current_time.tv_sec - last_time.tv_sec) * 1000
		+ (current_time.tv_usec - last_time.tv_usec) / 1000;
	if (elapsed_milliseconds >= delay)
	{
		fn();
		last_time = current_time;
	}
}
