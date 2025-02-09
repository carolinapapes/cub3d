# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: capapes <capapes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 17:21:33 by capapes           #+#    #+#              #
#    Updated: 2025/02/09 19:32:28 by capapes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Ilib -Wall -Wextra -Werror -g

# Directories
SRCDIR = .
LIBDIR = lib
OBJDIR = obj

# Libraries
MLX_LIB = $(LIBDIR)/libmlx42.a
MLX_FLAGS = -ldl -lglfw -pthread -lm

# Target executable
TARGET = main

# Source files and objects
MAIN_SRC = main.c minimap.c image_utils.c miniplayer.c miniview.c
MAIN_OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(MAIN_SRC))

# Ensure obj directory exists
$(shell mkdir -p $(OBJDIR))

# Build the target
all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_FLAGS)

# Compile .c files to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
