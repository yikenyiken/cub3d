NAME	= cub3D
SRC		= $(shell find ./src -iname "*.c")
OBJ		= $(SRC:.c=.o)
SCRIPT	:= ./install.sh
LIBMLX	:= ./mlx
FLAGS	= -Wall -Wextra -Werror #-g -fsanitize=address #-Wunreachable-code -Ofast

HEADERS	:= -I$(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -L/Users/$(USER)/goinfre/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit #-fsanitize=address
CC		= cc
RM		= rm -rf


all		: $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o		: %.c inc/cub3D.h
	$(CC) $(FLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

clean	:
	$(RM) $(OBJ) # $(LIBMLX)/build

fclean	: clean
	$(RM) $(NAME) $(LIBMLX)

re		: fclean all

t		: all clean
	clear && ./cub3D maps/map3.cub

install:
	sh $(SCRIPT)

.PHONY: clean, libmlx