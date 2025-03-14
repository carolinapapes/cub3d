/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:13 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 12:26:25 by capapes          ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/time.h>

# define WINDOW_SIZE 1024
# define WINDOW_SIZE 1024
# define HEIGHT_MIDDLE 512
# define GRID_SIZE 32
# define PLAYER_SIZE 16
# define PLAYER_MIDDLE 8

# define TERMINATE_MLX 1
# define FREE_START 2

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
# define HEX_PLAYER 0x00FF00FF
# define HEX_GRID 0xB0B0B0FF
# define HEX_WALL 0xB0B0B0CC
# define HEX_GREY 0xD5DBDBFF
# define HEX_RED 0xFF0000FF
# define HEX_GREEN 0x1ABC9CFF
# define HEX_BLUE 0x0000FFFF
# define HEX_PURPLE 0xFF00FFFF
# define HEX_CEILING 0x555555FF
# define HEX_FLOOR 0xBBBBBBFF

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define CENTER_X 1
# define CENTER_Y 2
# define PIXEL 4
# define CENTER 3    // CENTER_X & CENTER_Y
# define CENTER_PX 7 // CENTER & PIXEL

# define RESET_ORIGIN 1
# define SET_X 2
# define texture_setter 4
# define NORTH_TEXTURE 0
# define SOUTH_TEXTURE 1
# define WEST_TEXTURE 2
# define EAST_TEXTURE 3

typedef struct timeval	t_timeval;
typedef union u_color
{
	struct
	{
		unsigned char	a;
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		int				repeated;
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
	t_vector			origin;
	uint32_t			color;
	int					ongoing;
	mlx_texture_t		*image;
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
}						t_vector_full;

typedef struct s_int_pair
{
	int					x;
	int					y;
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
	t_vector			pos_center;
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
	double				angle_step;
	double				rotation_delta;
	double				fov;
	double				fov_delta_start;
	int					strip_height;
	double				double_pi;
	t_vector			zero;
	t_vector			limit_movement;
	t_vector			window_size;
	t_vector			player_size;
	t_vector			player_size_half;
	t_vector			map_size_px;
	t_vector			map_size;
	mlx_texture_t		*textures[4];
	t_player			player_initial;
	double				texture_width;
	double				texture_height;
	double				angle_sec[1024];

}						t_constants;

typedef enum e_image_type
{
	MINIPLAYER,
	MINIMAP,
	MINIVIEW,
	BACKGROUND,
	RENDER
}						t_image_type;

// ----------------------------[PARSER]----------------------------
int						parser_controler(char *file, t_start *start);
int						ft_split_count(char **split);
void					ft_split_free(char **split);
int						check_map(char *file_contents);
char					*find_first_map_line(char *input);
int						parse_map(char *line, char ***map);
int						parse_elements(char *line, char ***elements,
							t_start *start);
int						check_empty_lines_in_map(char **file);
char					*free_line(char **line);
void					free_start(t_start *start);
void					free_char_array(char ***split);
int						is_color(char *line, t_start *start);
int						line_in_map(char *line, int len);

//---------------------------- path ---------------------------------------------------------
int						is_path_valid(char *path);
int						is_texture(char *line, t_start *start);

//---------------------------- file_handler -------------------------------------------------
int						check_file_extension(char *file, char *extension_name);
int						get_line_length(int fd);
int						read_file(char *file, char **line);
char					*extract_content(char *file);


//                               INITILIAZER
int						is_map_character(char c);
int						start_map(t_start *start, char **map);

int						check_for_newlines_in_map(char *map);
int						empty_string(char *line);

int						check_fill_flood(t_start *start);
void					fill_flood(int **arr, int x, int y, t_int_pair size);

//                               FREE

int						free_parser(char *line, char **map, char **elements);

// ----------------------------[RENDER]----------------------------

// _aux_images.c
mlx_image_t				*get_miniplayer(void);
mlx_image_t				*get_miniview(void);
// mlx_image_t				*get_render(void);
// mlx_image_t				*get_minimap(void);
// void					init_background(void);
// mlx_image_t				*get_shadow(void);

// _bonus_remove_later.c
void					pov_iter(t_vector origin, double angle_fov);

// _minimap.c
void					update_mlx_miniplayer_pos(t_vector pos_delta, int axis);
int						get_cell_content(t_vector coord);
int						is_axis_wall(t_vector coord, t_axis axis,
							t_vector_full ray);
// void					set_minimap_pixel(t_vector coord);
void					set_pixel(mlx_image_t *image, t_vector pixel,
							uint32_t color);
void					update_mlx_miniplayer_pos(t_vector pos_delta, int axis);
void					update_minimap_pos(t_vector delta);
// void					init_minimap(void);
// void					set_textures(void);

// _parser_hardcoded.c
// void					init_player(void);

// _r_draw_minimap_utils.c
void					draw_intersect(t_vector_full vector, int color);
void					coordinate_paint(int x, int y);
// main.c
t_constants				game_constants(void);
t_start					*get_start(void);

// r_draw_utils.c
void					draw_point(t_vector point, int color);
void					draw_line(t_vector origin, t_vector direction, int len,
							int color);
void					draw_render(double distance, int iter);

// r_mlx_handler.c
// mlx_t					*get_window(void);
void					cub3d_init(void);

// r_mlx_image_handler.c
void					generic_matrix_iter(t_vector constrains,
							void fn(t_vector));
// void					set_pixels(mlx_image_t *image, int32_t color);
// void					clear_pixels(mlx_image_t *image);
// mlx_image_t				*get_image(t_vector size, t_vector origin);

// r_moves.c
void					rotate(int dir);
void					move(int axis, int dir);
// mlx_image_t				*get_image_full(void);

// r_player.c
t_player				*get_player(void);
// t_vector				get_player_center_px(void);

// r_ray_distance.c
t_vector_full			get_ray_intersection(t_vector_full ray, int axis);

// r_trigonometry.c
double					get_hypot(t_vector a, t_vector b);
double					get_side_len(t_vector a1, t_vector a2, t_vector tan,
							t_axis axis);
double					radian_overflow(double angle);
t_texture				*get_texture(void);
uint32_t				get_texture_color(void);
void					set_texture_x(double x_percentage, double direction);

void					clean_exit(int flags);
// r_texture.c
void					set_texture_image(int axis, int quadrant);
// void					toggle_minimap(void);
int						set_texture_y(double step);
// void					set_texture_step_y(double distance);
double					tends_to_zero(double x);
void					loop_window(void (*f)(void *));

/******************************************************************
 * 					BASIC MLX42 HANDLER FUNCTIONS
 *******************************************************************/

// r_window.c
mlx_t					*get_window(void);
void					loop_window(void (*f)(void *));

// r_image.c
mlx_image_t				*get_image(t_vector size, t_vector origin);
mlx_image_t				*get_image_full(void);
mlx_texture_t			*load_png(char *path);

// r_pixels.c
void					set_pixels(mlx_image_t *image, int32_t color);
void					clear_pixels(mlx_image_t *image);
uint32_t				get_pixel(uint8_t *pixels, uint32_t index);

/******************************************************************
 * 					CUB3D IMAGES
 *******************************************************************/
// r_render_images.c
void					set_background(void);
mlx_image_t				*get_shadow(void);
mlx_image_t				*get_render(void);

// r_minimap_images.c
void					toggle_minimap(void);
mlx_image_t				*get_minimap(void);
void					set_minimap(void);

// r_miniplayer.c
mlx_image_t				*get_miniplayer(void);
mlx_image_t				*get_miniview(void);

// ----------------------------[DELETE BEFORE SUBMIT]---------------
void					set_timeout(void (*fn)(void), int delay);
void					update_render(void);
void					set_player_pos(t_vector delta);
void					set_player_pov(double delta);
t_vector				vector_sum(t_vector a, t_vector b);
t_vector				get_player_side(int axis, int dir);
double					check_collition_in_axis(double delta, int axis);
#endif