# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: capapes <capapes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 17:21:33 by capapes           #+#    #+#              #
#    Updated: 2025/03/05 16:53:22 by capapes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Ilib -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address

# Directories
SRCDIR = src
LIBDIR = lib
OBJDIR = obj

# Libraries
MLXDIR = $(LIBDIR)/MLX42
MLX = $(MLXDIR)/build/libmlx42.a
MLX_FLAGS = -L$(MLXDIR)/build -lmlx42 -ldl -lm
MLX_REPO = https://github.com/codam-coding-college/MLX42.git

LIBFTDIR = $(LIBDIR)/libft
LIBFT = $(LIBFTDIR)/libft.a
LIBFT_FLAGS = -L$(LIBFTDIR) -lft
LIBFT_REPO = git@github.com:LeelooDa11as/Libft.git

# Build prerequisites first
PREQ = $(LIBFT) $(MLX)

# Include directories
INC = -I$(SRCDIR) -I$(LIBFTDIR) -I$(MLXDIR)/include

# macOS Specific Flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    MLX_FLAGS += -L/opt/homebrew/lib -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

# Linux Specific Flags
ifeq ($(UNAME_S), Linux)
	MLX_FLAGS += -lglfw -lGL -lm -lX11 -lXrandr -lXi -lXxf86vm -lpthread -ldl
endif

# Target executable
TARGET = main

# Source files and objects
MAIN_SRC = \
			_minimap.c \
			_r_draw_minimap_utils.c \
			file_handler.c \
			free_struct.c \
			ft_split_utils.c \
			initializer.c \
			main.c \
			parser_map.c \
			parser_map2.c \
			parser_map3.c \
			parser_utils.c \
			parser.c \
			path.c \
			r_draw_utils.c \
			r_map_checkers.c \
			r_minimap_images.c \
			r_mlx_handler.c \
			r_mlx_image_handler.c \
			r_moves.c \
			r_player.c \
			r_ray.c \
			r_ray_distance.c \
			r_render_images.c \
			r_texture.c \
			r_trigonometry.c
MAIN_OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(MAIN_SRC))
DEP_FILES = $(MAIN_OBJ:.o=.d)

# Build the target (ensuring prerequisites are compiled first)
all: | $(OBJDIR) $(PREQ) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(MLX_FLAGS) $(LIBFT_FLAGS)

# Compile .c files to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files if they exist
-include $(DEP_FILES)

# Build the libraries
$(LIBFT):
	@if [ ! -d "$(LIBFTDIR)" ]; then git clone $(LIBFT_REPO) $(LIBFTDIR); fi
	make -C $(LIBFTDIR)

$(MLX):
	@if [ ! -d "$(MLXDIR)" ]; then git clone $(MLX_REPO) $(MLXDIR); fi
	cmake -B $(MLXDIR)/build -S $(MLXDIR)
	cmake --build $(MLXDIR)/build

# Clean up
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@make -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(LIBFTDIR) $(MLXDIR)

re: clean all

.PHONY: all clean fclean re
