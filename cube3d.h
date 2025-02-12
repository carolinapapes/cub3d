/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:13 by capapes           #+#    #+#             */
/*   Updated: 2025/02/12 08:50:20 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "lib/MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 256 // Maybe should be fixed
# define HEIGHT 256 // Variable
# define WINDOW_TITLE "Cube3D"

# define WALL 1
# define PLAYER 2
# define GRID 4

# define SET_PLAYER 1
# define SET_INSTANCE 2
# define SET_VIEW 3

# define PLAYER_COLOR 0x00FF0000FF
# define FOV_COLOR 0xB0B0B0B0
# define GRID_COLOR 0xB0B0B0FF
# define WALL_COLOR 0xB0B0B0FF

// Sizes definitions are variables
# define GRID_SIZE 16
# define PLAYER_SIZE 8
# define MAP_SIZE_X 16
# define MAP_SIZE_Y 16

# define FOV 60 // field of view maybe fixed

typedef enum e_axis
{
	X,
	Y
}				t_axis;

typedef enum e_dir
{
	NEGATIVE = -1,
	POSITIVE = 1
}				t_dir;

void			iter_image(mlx_image_t *image, void(fn)(mlx_image_t *, uint32_t,
						uint32_t));
mlx_image_t		*mlx_add_image(mlx_t *mlx, uint32_t width, uint32_t height, int *pos);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			set_minimap(mlx_t *mlx);
int				is_fixed_object(uint32_t x, uint32_t y);
void			set_player(mlx_t *mlx, int x, int y);
void			miniplayer_hook(int axis, int sign);
mlx_image_t		*get_player(void);
void			mlx_clear_image(mlx_image_t *image);
mlx_image_t		*get_view(mlx_t *mlx);
void			view_move(int x, int y);
void			view_rotate(int dir);
#endif