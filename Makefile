# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: capapes <capapes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 17:21:33 by capapes           #+#    #+#              #
#    Updated: 2025/02/12 19:58:13 by capapes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Ilib -Wall -Wextra -Werror -g -fsanitize=address

# Directories
SRCDIR = .
LIBDIR = lib
OBJDIR = obj
MLXDIR = $(LIBDIR)/MLX42

# Libraries
MLX_LIB = $(MLXDIR)/build/libmlx42.a
MLX_FLAGS = -L$(MLXDIR)/build -lmlx42 -ldl -lm

# Libft
LIBFT_PATH 	= $(LIBDIR)/libft
LIBFT_NAME = libft
LIBFT_LINK	= -L${LIBDIR} -lft

# Functions
define make_lib
    @echo "Making $1..."
    @make -C $2 
    @echo "$(GREEN)📚completed		$1$(DEF_COLOR)"
endef


# macOS Specific Flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    MLX_FLAGS += -L/opt/homebrew/lib -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

ifeq ($(UNAME_S), Linux)
	MLX_FLAGS += -lglfw -lGL -lm -lX11 -lXrandr -lXi -lXxf86vm -lpthread -ldl
endif

# Target executable
TARGET = main 

# Source files and objects
MAIN_SRC = main.c minimap.c image_utils.c miniplayer.c miniview.c parser.c ft_split_utils.c
MAIN_OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(MAIN_SRC))

# Build the target
all: make_libs $(MLX_LIB) $(TARGET)

make_libs:
	$(call make_lib,$(LIBFT_NAME),$(LIBFT_PATH))

$(TARGET): $(MAIN_OBJ) $(MLX_LIB) $(LIBFT_PATH)/libft.a
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_FLAGS)

# Compile .c files to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# # Clone and build MLX42
$(MLX_LIB):
	git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR)
	cmake -B $(MLXDIR)/build -S $(MLXDIR) 
	cmake --build $(MLXDIR)/build

# Clean up
clean:
	rm -rf $(OBJDIR) $(TARGET) $(MLXDIR)
	@make -C $(LIBFT_PATH) clean

re: clean all


.PHONY: all clean
