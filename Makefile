# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: capapes <capapes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 17:21:33 by capapes           #+#    #+#              #
#    Updated: 2025/02/11 22:35:26 by capapes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Ilib -Wall -Wextra -Werror -g

# Directories
SRCDIR = .
LIBDIR = lib
OBJDIR = obj
MLXDIR = $(LIBDIR)/MLX42

# Libraries
MLX_LIB = $(MLXDIR)/build/libmlx42.a
MLX_FLAGS = -L$(MLXDIR)/build -lmlx42 -ldl -lm

# macOS Specific Flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    MLX_FLAGS += -L/opt/homebrew/lib -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

# Target executable
TARGET = main

# Source files and objects
MAIN_SRC = main.c minimap.c image_utils.c miniplayer.c miniview.c
MAIN_OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(MAIN_SRC))

# Build the target
all: $(MLX_LIB) $(TARGET)

$(TARGET): $(MAIN_OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_FLAGS)

# Compile .c files to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# # Clone and build MLX42
$(MLX_LIB):
	cmake -B $(MLXDIR)/build -S $(MLXDIR) 
	cmake --build $(MLXDIR)/build

# Clean up
clean:
	rm -rf $(OBJDIR) $(TARGET) $(MLXDIR)/build

re: clean all


.PHONY: all clean
