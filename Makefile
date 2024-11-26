NAME			:= cub3D
NAME_BONUS		:= cub3D_bonus
CFLAGS			:= -Wextra -Wall -Werror
LIBMLX			:= lib/MLX42
INCLUDE			:= cub3d_mandatory/include/cub3d.h
INCLUDE_BONUS	:= cub3d_bonus/include/cub3d_bonus.h
HEADERS			:= -I include -I $(LIBMLX)/include
LIBS			:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS			:= $(shell find cub3d_mandatory/src -iname "*.c")
OBJS			:= ${SRCS:.c=.o}
SRCS_BONUS		:= $(shell find cub3d_bonus/src -iname "*_bonus.c")
OBJS_BONUS		:= ${SRCS_BONUS:.c=.o}
MAP				:= maps/maze.cub

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) 

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

bonus: libmlx $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS)

%_bonus.o: %_bonus.c $(INCLUDE_BONUS)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@rm -rf $(LIBMLX)

re: clean all

m: $(NAME)
	@./$< $(MAP)

b: $(NAME_BONUS)
	@./$< $(MAP)

install:
	-@git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42
	-@cd ~/goinfre && mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
	@brew install glfw

.PHONY: clean, libmlx