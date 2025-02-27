/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:13 by capapes           #+#    #+#             */
/*   Updated: 2025/02/27 18:16:39 by capapes          ###   ########.fr       */
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

# define WIDTH 			1024
# define HEIGHT 		1024
# define GRID_SIZE 		64
# define PLAYER_SIZE 	32
# define PLAYER_MIDDLE 	16

# define WINDOW_TITLE "Cube3D"

# define WALL 1
# define SPACE 2
# define GRID 4
# define N 8
# define S 16
# define E 32
# define W 64
# define PLAYER 120
# define OUTSIDE 128

// ----------------------------[COLORS]----------------------------
# define HEX_PLAYER 0x00FF00FF
# define HEX_GRID 0xB0B0B0FF
# define HEX_WALL 0xB0B0B0CC
# define HEX_GREY 0xD5DBDBFF
# define HEX_RED 0xE72D2DFF
# define HEX_GREEN 0x1ABC9CFF
# define HEX_BLUE 0x0000FFFF
# define HEX_PURPLE 0xFF00FFFF

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define CENTER_X 1
# define CENTER_Y 2
# define PIXEL 4
# define CENTER 3 // CENTER_X & CENTER_Y
# define CENTER_PX 7 // CENTER & PIXEL

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

typedef struct s_vector_full
{
	t_vector			origin;
	t_vector			end;
	t_vector			direction;
	t_vector			quadrant;
	t_vector			tan;
	double				distance;
}					t_vector_full;

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

typedef struct s_player
{
	t_vector			pos;
	double				pov;
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

typedef struct s_constants
{
	double		angle_step;
	double		fov;
	int			strip_width;
	double		fov_delta_start;
	int			strip_height;
	t_vector	dir_x;
	t_vector	dir_y;
}				t_constants;

// ----------------------------[PARSER]----------------------------
t_start					*parser(int argc, char **argv);
int						ft_split_count(char **split);
void					ft_split_free(char **split);

// ----------------------------[RENDER]----------------------------

// _aux_images.c
mlx_image_t				*get_player_image(void);
mlx_image_t				*get_view_image(void);
mlx_image_t				*get_aux_img(void);
mlx_image_t				*get_render_image(void);
void					get_minimap_image(void);

// _bonus_remove_later.c
void					pov_iter(t_vector origin, double angle_fov);

// _minimap.c
void					update_mlx_player(void);
void					draw_minimap(mlx_image_t *image,
							uint32_t x, uint32_t y);
int						is_fixed_object(uint32_t x, uint32_t y);
int						is_axis_wall(t_vector coord, t_axis axis,
							t_vector_full ray);

// _parser_hardcoded.c
void					player_init(void);

// _r_draw_minimap_utils.c
void					draw_intersect(t_vector_full vector, int color);

// main.c
t_constants				game_constants(void);

// r_draw_utils.c
void					draw_point(t_vector point, int color);
void					draw_line(t_vector origin, t_vector direction,
							int len, int color);
void					draw_line_render(t_vector origin, t_vector direction,
							int len, int color);

// r_mlx_handler.c
mlx_t					*get_mlx(void);
void					cub3d_init(void);

// r_mlx_image_handler.c
void					iter_image(mlx_image_t *image, void fn(mlx_image_t *,
								uint32_t, uint32_t));
void					image_full_color(mlx_image_t *image, int32_t color);
void					mlx_clear_image(mlx_image_t *image);
mlx_image_t				*new_image(t_vector size, t_vector origin);

// r_moves.c
void					player_rotate(int dir);
void					player_move(t_axis axis, int dir);
mlx_image_t				*new_image_full(void);

// r_player.c
t_player				set_player(t_vector position_delta, double angle_delta);
t_vector				get_player_pos(int flag);

// r_ray_distance.c
t_vector_full			intersect(t_vector_full ray, int axis);

// ----------------------------[DELETE BEFORE SUBMIT]---------------
void					ft_print_split(char **split);

#endif