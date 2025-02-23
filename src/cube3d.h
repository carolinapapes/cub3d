/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:21:13 by capapes           #+#    #+#             */
/*   Updated: 2025/02/23 18:50:06 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# define WIDTH 256  // Maybe should be fixed
# define HEIGHT 256 // Variable
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
# define WALL_COLOR 0xB0B0B0FF

// Sizes definitions are variables
# define MAP_SIZE_X 16
# define MAP_SIZE_Y 16
# define GRID_SIZE 16
# define PLAYER_SIZE 8

# define FOV 60 // field of view maybe fixed

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

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
}						t_coord;

typedef	struct s_int_pair
{
	int	x;
	int	y;
}						t_int_pair;

typedef struct s_map
{
	t_coord				size;
	char				**map;
	t_int_pair			size_int;
	int					**map_int;
}						t_map;

typedef struct s_start
{
	int					n_fd;
	int					s_fd;
	int					w_fd;
	int					e_fd;
	t_color				floor;
	t_color				ceiling;
	t_map				map;
	t_coord				player;
	int					player_dir;
	t_int_pair          player_pos;
}						t_start;

typedef enum e_axis
{
	X,
	Y
}						t_axis;

typedef enum e_dir
{
	NEGATIVE = -1,
	POSITIVE = 1
}						t_dir;

// ----------------------------[PARSER]----------------------------
t_start					*parser_controler(int argc, char **argv);
int						ft_split_count(char **split);
void					ft_split_free(char **split);
int						check_map(char *file_contents);
char					*find_first_map_line(char *input);
char					**get_map(char *line);
char					**get_elements(char *line);
int						check_empty_lines_in_map(char **file);
char					*free_line(char **line);
void					free_start(t_start *start);

//---------------------------- file_handler -------------------------
int						check_file_extension(char *file);
int						get_line_length(int fd);
char					*read_file(char *file);

//                               INITILIAZER
t_start					*start_initializer(char *line);
int						is_map_character(char c);

int						check_fill_flood(t_start *start);
void					fill_flood(int	**arr, int x, int y, t_int_pair size);


// ----------------------------[RENDER]----------------------------
void					iter_image(mlx_image_t *image, void(fn)(mlx_image_t *,
								uint32_t, uint32_t));
mlx_image_t				*mlx_add_image(mlx_t *mlx, uint32_t width,
							uint32_t height, int *pos);
int32_t					ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void					set_minimap(mlx_t *mlx);
int						is_fixed_object(uint32_t x, uint32_t y);
void					set_player(mlx_t *mlx, t_coord player);
void					miniplayer_hook(int axis, int sign);
mlx_image_t				*get_player(void);
void					mlx_clear_image(mlx_image_t *image);
mlx_image_t				*get_view(mlx_t *mlx);
void					view_move(t_coord movement);
void					view_rotate(int dir);

// ----------------------------[DELETE BEFORE SUBMIT]---------------
void					ft_print_split(char **split);

#endif