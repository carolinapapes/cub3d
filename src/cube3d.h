/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:13 by capapes           #+#    #+#             */
/*   Updated: 2025/03/07 15:55:22 by capapes          ###   ########.fr       */
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
#include <sys/stat.h>

# define WIDTH 				1024
# define HEIGHT 			1024
# define HEIGHT_MIDDLE 		512
# define GRID_SIZE 			32
# define PLAYER_SIZE 		16
# define PLAYER_MIDDLE 		8

# define TERMINATE_MLX 		1
# define FREE_START 		2

# define WINDOW_TITLE "Cube3D"

# define WALL 1
# define SPACE 5
# define GRID 4
# define N 8
# define S 16
# define E 32
# define W 64
# define PLAYER 120
# define OUTSIDE 128

// ----------------------------[COLORS]----------------------------
# define HEX_PLAYER 	0x00FF00FF
# define HEX_GRID 		0xB0B0B0FF
# define HEX_WALL 		0xB0B0B0CC
# define HEX_GREY 		0xD5DBDBFF
# define HEX_RED 		0xFF0000FF
# define HEX_GREEN 		0x1ABC9CFF
# define HEX_BLUE 		0x0000FFFF
# define HEX_PURPLE 	0xFF00FFFF
# define HEX_CEILING 	0x555555FF
# define HEX_FLOOR 		0xBBBBBBFF

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

typedef struct s_texture
{
	t_vector			pixel;
	t_vector			step;
	t_vector			origin;
	uint32_t			color;
	mlx_texture_t		*image[4];
	int					ongoing;
}						t_texture;

typedef struct s_vector_full
{
	t_vector			origin;
	t_vector			end;
	t_vector			direction;
	t_vector			quadrant;
	t_vector			tan;
	double				distance;
	int					axis;
}					t_vector_full;

typedef	struct s_int_pair
{
	int	x;
	int	y;
}						t_int_pair;

typedef struct s_map
{
	t_vector			size;
	char				**map;
	t_int_pair			size_int;
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
	char				*n_fd;
	char				*s_fd;
	char				*w_fd;
	char				*e_fd;
	t_color				floor;
	t_color				ceiling;
	t_map				map;
	t_vector			player;
	int					player_dir;
	t_int_pair			player_pos;
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

# define PLAYER_MOVE_X 1
# define PLAYER_MOVE_Y 2

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
	double		double_pi;
	t_vector	dir_x;
	t_vector	dir_y;
	t_vector	limit_movement;
	t_vector	zero;
	double		texture_width;
	double		texture_height;
	double		angle_sec[1024];
}				t_constants;

typedef enum e_image_type
{
	MINIPLAYER,
	MINIMAP,
	MINIVIEW,
	BACKGROUND,
	RENDER
}	t_image_type;

// ----------------------------[PARSER]----------------------------
int						parser_controler(int argc, char **argv, t_start *start);
int						ft_split_count(char **split);
void					ft_split_free(char **split);
int						check_map(char *file_contents);
char					*find_first_map_line(char *input);
int						parse_map(char *line, char ***map);
int						parse_elements(char *line, char ***elements, t_start *start);
int						check_empty_lines_in_map(char **file);
char					*free_line(char **line);
void					free_start(t_start *start);
void					free_char_array(char ***split);
int						check_four_dir(t_start *start, char **elements);
int						check_for_color(t_start *start, char **elements);

//---------------------------- path ---------------------------------------------------------
int						is_path_valid(char *path);

//---------------------------- file_handler -------------------------------------------------
int						check_file_extension(char *file, char *extension_name);
int						get_line_length(int fd);
int						read_file(char *file, char **line);

//                               INITILIAZER
int						start_initializer(t_start *start, char **map, char **elements);
int						is_map_character(char c);

int						check_fill_flood(t_start *start);
void					fill_flood(int	**arr, int x, int y, t_int_pair size);

// ----------------------------[RENDER]----------------------------

// _aux_images.c
mlx_image_t				*get_miniplayer_image(void);
mlx_image_t				*get_miniview_image(void);
mlx_image_t				*get_render_image(void);
mlx_image_t				*get_minimap_image(void);
void					init_background(void);
mlx_image_t				*get_shadow_image(void);

// _bonus_remove_later.c
void					pov_iter(t_vector origin, double angle_fov);

// _minimap.c
void					update_mlx_miniplayer_pos(t_vector pos_delta, int axis);
int						get_cell_content(t_vector coord);
int						is_axis_wall(t_vector coord, t_axis axis,
							t_vector_full ray);
void					draw_minimap(t_vector coord);
void					draw_pixel(mlx_image_t *image, t_vector pixel, uint32_t color);
void					update_mlx_miniplayer_pos(t_vector pos_delta, int axis);
void					update_minimap_pos(t_vector position, t_vector position_delta);
void					init_minimap(void);

// _parser_hardcoded.c
void					init_player(void);

// _r_draw_minimap_utils.c
void					draw_intersect(t_vector_full vector, int color);
void					coordinate_paint(int x, int y);
// main.c
t_constants				game_constants(void);
t_start					*get_start(void);

// r_draw_utils.c
void					draw_point(t_vector point, int color);
void					draw_line(t_vector origin, t_vector direction,
							int len, int color);
void					draw_render(double distance, int iter);

// r_mlx_handler.c
mlx_t					*get_mlx(void);
void					cub3d_init(void);

// r_mlx_image_handler.c
void					generic_matrix_iter(t_vector constrains, void fn(t_vector));
void					image_full_color(mlx_image_t *image, int32_t color);
void					mlx_clear_image(mlx_image_t *image);
mlx_image_t				*new_image(t_vector size, t_vector origin);

// r_moves.c
void					player_rotate(int dir);
void					player_move(t_axis axis, int dir);
mlx_image_t				*new_image_full(void);

// r_player.c
t_player				set_player(t_vector position_delta, double angle_delta);
t_vector				get_player_center_px(void);

// r_ray_distance.c
t_vector_full			get_ray_intersection(t_vector_full ray, int axis);

// r_trigonometry.c
double					get_hypot(t_vector a, t_vector b);
double					get_side_len(t_vector a1, t_vector a2, t_vector tan,
							t_axis axis);
double					radian_overflow(double angle);
t_texture				get_texture(void);
uint32_t				get_pixel_info(mlx_texture_t *texture,
							uint32_t pixel_index);
uint32_t				get_texture_color(t_texture texture);
void					set_texture_x(double x_percentage);

void					clean_exit(int flags);
// r_texture.c
void					set_ongoing_view_wall(int axis, int quadrant);

// ----------------------------[DELETE BEFORE SUBMIT]---------------
void					ft_print_split(char **split);

#endif