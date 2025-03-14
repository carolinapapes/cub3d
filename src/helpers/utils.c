/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 05:12:00 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 17:46:51 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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

void	print_error(void)
{
	write(2, "Error\n", 6);
	return ;
}

void	clean_exit(int flags)
{
	mlx_t	*mlx;
	t_start	*start;

	if (flags & TERMINATE_MLX)
	{
		mlx = get_window();
		mlx_terminate(mlx);
	}
	if (flags & FREE_START)
	{
		start = get_start();
		free_start(start);
	}
	print_error();
	exit(EXIT_FAILURE);
}
