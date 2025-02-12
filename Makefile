# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: capapes <capapes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 17:21:33 by capapes           #+#    #+#              #
#    Updated: 2025/02/12 21:25:07 by capapes          ###   ########.fr        #
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

# Helper function to clone a repo if it doesn't exist
define clone_if_missing
	@if [ ! -d "$(1)" ]; then \
		git clone $(2) $(1); \
	fi
endef

# Target executable
TARGET = main

# Source files and objects
MAIN_SRC = main.c minimap.c image_utils.c miniplayer.c miniview.c parser.c ft_split_utils.c
MAIN_OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(MAIN_SRC))
DEP_FILES = $(MAIN_OBJ:.o=.d)

# Build the target (ensuring prerequisites are compiled first)
all: $(PREQ) $(TARGET)

$(TARGET): $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(MLX_FLAGS) $(LIBFT_FLAGS)

# Compile .c files to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files if they exist
-include $(DEP_FILES)

# Build the libraries
$(LIBFT):
	$(call clone_if_missing, $(LIBFTDIR), $(LIBFT_REPO))
	make -C $(LIBFTDIR)

$(MLX):
	$(call clone_if_missing, $(MLXDIR), $(MLX_REPO))
	cmake -B $(MLXDIR)/build -S $(MLXDIR)
	cmake --build $(MLXDIR)/build

# Clean up
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@make -C $(LIBFTDIR) clean

re: clean all

.PHONY: all clean re
