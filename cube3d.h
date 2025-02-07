/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:13 by capapes           #+#    #+#             */
/*   Updated: 2025/02/07 18:52:31 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "lib/MLX42.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 512
# define HEIGHT 512
# define WINDOW_TITLE "Cube3D"

# define WALL 1
# define ITEM 2
# define PLAYER 4
# define GRID 8

# define SET_PLAYER 1
# define SET_INSTANCE 2
# define UPDATE_PLAYER 3
# define PLAYER_SIZE 16
# define PLAYER_COLOR 0x00FF00FFFF
# define GRID_COLOR 0xB0B0B0FF
# define WALL_COLOR 0xFFFFFFFF
# define GRID_SIZE 32

# define X 1
# define Y 2
# define POSITIVE 1
# define NEGATIVE -1

typedef struct s_minicolors
{
	uint32_t	wall;
	uint32_t	grid;
	uint32_t	item;
	uint32_t	player;
}				t_minicolors;

typedef struct s_miniplayer
{
	int			x;
	int			y;
	int			size;
	mlx_image_t	*image;
}				t_miniplayer;

void			iter_image(mlx_image_t *image, void(fn)(mlx_image_t *, uint32_t,
						uint32_t));
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			set_minimap(mlx_t *mlx);
void			set_player(mlx_t *mlx, int x, int y);
void			miniplayer_hook(int axis, int sign);

#endif