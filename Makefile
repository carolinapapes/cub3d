# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: capapes <capapes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 17:21:33 by capapes           #+#    #+#              #
#    Updated: 2025/01/31 17:21:34 by capapes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
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

# Source files
MAIN_SRC = $(SRCDIR)/main.c
MAIN_OBJ = $(OBJDIR)/main.o

# Create obj directory if it doesn't exist
$(shell mkdir -p $(OBJDIR))

# Rules
all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(LIB_OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_FLAGS)

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)