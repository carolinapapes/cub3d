/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_window.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:13:55 by capapes           #+#    #+#             */
/*   Updated: 2025/03/12 20:43:42 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static mlx_t	*init_window(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (!mlx)
		clean_exit(FREE_START);
	return (mlx);
}

mlx_t	*get_window(void)
{
	static mlx_t	*mlx;

	if (!mlx)
		mlx = init_window();
	return (mlx);
}

void	loop_window(void (*f)(void *))
{
	mlx_t	*mlx;
	int		res;

	mlx = get_window();
	res = mlx_loop_hook(mlx, f, mlx);
	if (!res)
		clean_exit(TERMINATE_MLX | FREE_START);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
