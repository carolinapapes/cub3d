/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:13 by capapes           #+#    #+#             */
/*   Updated: 2025/02/23 19:51:32 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define WIDTH 1024  // Maybe should be fixed
# define HEIGHT 1024 // Variable
# define WINDOW_TITLE "Cube3D"

# define WALL 1
# define SPACE 2
# define GRID 4
# define N 8
# define S 16
# define E 32
# define W 64
# define PLAYER 120

# define SET_PLAYER 1
# define SET_INSTANCE 2
# define SET_VIEW 3

# define PLAYER_COLOR 0x00FF00FF
# define FOV_COLOR 0xB0B0B0B0
# define GRID_COLOR 0xB0B0B0FF
# define WALL_COLOR 0xB0B0B0CC

// Sizes definitions are variables
# define MAP_SIZE_X 16
# define MAP_SIZE_Y 16
# define GRID_SIZE 64
# define PLAYER_SIZE 32
# define PLAYER_MIDDLE 16
# define HEX_RED 0xFF0000FF
# define HEX_GREEN 0x00FF00FF

# define FOV 60 // field of view maybe fixed

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define C3D_MLX_INIT 1
# define C3D_MLX_CLOSE 2
# define C3D_MLX_GET 3

# define PLAYER_ORIGIN 1
# define PLAYER_CENTER 2
# define PLAYER_PIXEL_CENTER 3

typedef union u_color
{
	struct
	{
		unsigned char	a;
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
	};
	unsigned int		rgba;
}						t_color;

typedef union u_coord
{
	struct
	{
		double			x;
		double			y;
	};
	double				arr[2];
}						t_vector;

typedef struct s_map
{
	t_vector			size;
	char				**map;
	int					**map_int;
}						t_map;

typedef struct check_point
{
	t_vector			to_player;
	double				distance_to_player;
	t_vector			to_grid;
	double				distance_to_grid;
}						t_check_point;

typedef struct s_start
{
	int					n_fd;
	int					s_fd;
	int					w_fd;
	int					e_fd;
	t_color				floor;
	t_color				ceiling;
	t_map				map;
	t_vector			player;
	int					player_dir;

}						t_start;

typedef struct s_pov
{
	double				angle;
	t_vector			t_ratio;
	t_vector			quadrant;
	double				tan;
}						t_pov;

typedef struct s_player
{
	t_vector			pos;
	mlx_image_t			*mlx_player;
	mlx_image_t			*mlx_view;
	t_pov				pov;
}						t_player;

typedef enum e_axis
{
	X = 0,
	Y = 1
}						t_axis;

typedef enum e_dir
{
	NEGATIVE = -1,
	POSITIVE = 1
}						t_dir;

// ----------------------------[PARSER]----------------------------
t_start					*parser(int argc, char **argv);
int						ft_split_count(char **split);
void					ft_split_free(char **split);

// ----------------------------[RENDER]----------------------------

// bonus
mlx_t					*get_mlx(void);
void					player_rotate(int dir);
void					player_move(t_axis axis, int dir);
mlx_image_t				*init_player_image(void);
void					minimap_init(void);
int						is_fixed_object(uint32_t x, uint32_t y);
mlx_image_t				*new_image(t_vector size, t_vector origin);
void					update_mlx_player(t_player *player);
void					update_mlx_view(t_player player,
							t_vector grid_distance);
t_player				set_player(t_vector position_delta, double angle_delta);
t_vector				get_grid_distance(t_player player);
mlx_image_t				*get_view(void);

void					player_init(void);
void					cub3d_init(void);

void					iter_image(mlx_image_t *image, void fn(mlx_image_t *,
								uint32_t, uint32_t));

void					mlx_clear_image(mlx_image_t *image);

void					draw_pixel(mlx_image_t *image, t_vector pixel,
							int32_t color);
t_vector				get_player_pos(int flag);
;
void					image_full_color(mlx_image_t *image, int32_t color);
mlx_image_t				*new_image_full(void);
void					draw_point(mlx_image_t *image, t_vector point,
							int color);
t_player				get_player(void);
void					draw_intersect(t_player player, t_vector pos,
							t_vector point, int color);
// ----------------------------[DELETE BEFORE SUBMIT]---------------
void					ft_print_split(char **split);

# define DEBUG_PRINT() printf("%s:%d: ", __FILE__, __LINE__);

#endif