NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -Ofast
LIBMLX	:= lib/MLX42
SCRIPT	:= ./install.zsh
INCLUDE	:= include/cub3d.h
HEADERS	:= -I include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -L/Users/$(USER)/goinfre/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME) $(LIBMLX)

re: clean all

t: $(NAME)
	@./$(NAME) maps/map.cub

install:
	@zsh $(SCRIPT)

.PHONY: clean, libmlx