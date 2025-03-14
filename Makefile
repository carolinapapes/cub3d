# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: capapes <capapes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 17:21:33 by capapes           #+#    #+#              #
#    Updated: 2025/03/14 14:07:06 by capapes          ###   ########.fr        #
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

# NAME executable
NAME = main

PARSER = colour.c

CUB3D_TO_MLX = 	image.c \
				pixels.c \
				window.c

EVENTS = 		collitions.c \
				moves.c \
				events_handler.c

MINIMAP = 		draw_minimap.c \
				minimap.c \
				miniplayer.c \
				set_minimap_pos.c

RENDER = 		draw_render.c \
				player.c \
				ray.c \
				ray_2.c \
				render.c \
				texture.c

HELPERS = 		utils.c \
				map_utils.c \
				trigonometry.c \
				vector_operations.c \
				game_constants.c

DIRS =			parser \
				helpers \
				cub3d_to_mlx \
				events \
				minimap \
				render

# AUTOMATICALLY GENERATE OBJECT FILES FOR DIRS
DIRS_OBJ_FILES = $(foreach directory,$(DIRS), \
	$(patsubst $(SRCDIR)/$(directory)/%.c, $(OBJDIR)/$(directory)/%.o, \
		$(addprefix $(SRCDIR)/$(directory)/, $($(shell echo $(directory) | tr a-z A-Z)))))

# COLORS
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
ORANGE = \033[0;31m
GREEN = \033[0;92m

# Source files and objects
MAIN_SRC = 	file_handler.c \
			free_struct.c \
			initializer.c \
			main.c \
			parser_map.c \
			parser_map2.c \
			parser_map3.c \
			parser_utils.c \
			parser.c \
			path.c 
MAIN_OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(MAIN_SRC))
DEP_FILES = $(MAIN_OBJ:.o=.d)

# OBJECT FILES
OBJ_FILES = $(MAIN_OBJ) $(DIRS_OBJ_FILES)

# RULES
all: | $(PREQ) $(NAME)

# FINAL NAME
$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(INC) -o $@ $^ $(MLX_FLAGS) $(LIBFT_FLAGS)
	@echo "$(GREEN)📚completed		$(NAME)$(DEF_COLOR)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -MT $@ -MMD -MP $(CFLAGS) $(INC) -c $< -o $@
	@echo "$(GRAY)⏳compiling		$<$(DEF_COLOR)" 

define compile_rule
$(OBJDIR)/$1/%.o: $(SRCDIR)/$1/%.c
	@mkdir -p $$(dir $$@)
	@$(CC) $(FLAGS) $(INC) -c $$< -o $$@
	@echo "$(GRAY)⏳compiling $1	$$<$(DEF_COLOR)"
endef

$(foreach directory,$(DIRS),$(eval $(call compile_rule,$(directory))))

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

# CLEAN OBJECT FILES
clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean
	@echo "$(ORANGE)🧹cleaned		${NAME}$(DEF_COLOR)"

# FULL CLEAN
fclean:
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)
	@rm -rf $(LIBFTDIR)
	@rm -rf $(MLXDIR)
	@echo "$(ORANGE)🧹fcleaned		${NAME}$(DEF_COLOR)"

# REBUILD EVERYTHING
re: fclean all

.PHONY: re fclean clean all

# END OF FILE
