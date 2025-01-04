NAME			= cub3D
NAME_BONUS		= cub3D_bonus
CFLAGS			=  -Wextra -Wall -Werror
LIBMLX			= lib/MLX42
LIBS			= $(LIBMLX)/build/libmlx42.a -L/Users/$(USER)/goinfre/homebrew/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
HEADERS			= -I $(LIBMLX)/include
INCLUDE			= cub3d_mandatory_part/include/cub3d.h
INCLUDE_BONUS	= cub3d_bonus_part/include/cub3d_bonus.h
MAP				= maps/maze.cub

PARSER_MAN		= cub3d_mandatory_part/src/parser
GRAPHICS_MAN	= cub3d_mandatory_part/src/graphics
SRCS			= cub3d_mandatory_part/src/cub3d.c $(GRAPHICS_MAN)/3d_map.c						\
				  $(GRAPHICS_MAN)/collision.c $(GRAPHICS_MAN)/cub3d_utils.c						\
				  $(GRAPHICS_MAN)/init_cub3d.c $(GRAPHICS_MAN)/init_mlx.c						\
				  $(GRAPHICS_MAN)/key_events.c $(GRAPHICS_MAN)/math_utils.c						\
				  $(GRAPHICS_MAN)/mlx_images.c $(GRAPHICS_MAN)/mlx_textures.c					\
				  $(GRAPHICS_MAN)/update_player.c $(GRAPHICS_MAN)/cleanup.c						\
				  $(GRAPHICS_MAN)/ray_casting.c $(GRAPHICS_MAN)/rays.c							\
				  $(PARSER_MAN)/check_walls.c $(PARSER_MAN)/lib_tools/lib_tools_1.c 			\
				  $(PARSER_MAN)/lib_tools/lib_tools_2.c $(PARSER_MAN)/check_data.c				\
				  $(PARSER_MAN)/lib_tools/lib_tools_3.c $(PARSER_MAN)/lib_tools/lib_tools_4.c	\
				  $(PARSER_MAN)/lib_tools/lib_tools_5.c $(PARSER_MAN)/parssing.c				\
				  $(PARSER_MAN)/lib_tools/lib_tools_6.c $(PARSER_MAN)/lib_tools/lib_tools_7.c
OBJS			= ${SRCS:.c=.o}

PARSER_BON		= cub3d_bonus_part/src/parser
GRAPHICS_BON	= cub3d_bonus_part/src/graphics
SRCS_BONUS		= cub3d_bonus_part/src/cub3d_bonus.c $(GRAPHICS_BON)/update_player_bonus.c		\
 				  $(GRAPHICS_BON)/2d_map_bonus.c $(GRAPHICS_BON)/3d_map_bonus.c					\
 				  $(GRAPHICS_BON)/cleanup_bonus.c $(GRAPHICS_BON)/collision_bonus.c				\
 				  $(GRAPHICS_BON)/cub3d_utils_bonus.c $(GRAPHICS_BON)/draw_player_bonus.c		\
 				  $(GRAPHICS_BON)/init_cub3d_bonus.c $(GRAPHICS_BON)/init_mlx_bonus.c			\
 				  $(GRAPHICS_BON)/key_events_bonus.c $(GRAPHICS_BON)/math_utils_bonus.c			\
 				  $(GRAPHICS_BON)/mlx_images_bonus.c $(GRAPHICS_BON)/mlx_textures_bonus.c		\
 				  $(GRAPHICS_BON)/ray_casting_bonus.c $(GRAPHICS_BON)/rays_bonus.c				\
 				  $(PARSER_BON)/check_data_bonus.c $(PARSER_BON)/check_walls_bonus.c			\
 				  $(PARSER_BON)/lib_tools/lib_tools_1_bonus.c $(PARSER_BON)/parssing_bonus.c	\
 				  $(PARSER_BON)/lib_tools/lib_tools_2_bonus.c 									\
 				  $(PARSER_BON)/lib_tools/lib_tools_3_bonus.c									\
 				  $(PARSER_BON)/lib_tools/lib_tools_4_bonus.c									\
 				  $(PARSER_BON)/lib_tools/lib_tools_5_bonus.c									\
 				  $(PARSER_BON)/lib_tools/lib_tools_6_bonus.c									\
 				  $(PARSER_BON)/lib_tools/lib_tools_7_bonus.c
OBJS_BONUS		= ${SRCS_BONUS:.c=.o}

all	: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build

bonus: libmlx $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS)

%_bonus.o: %_bonus.c $(INCLUDE_BONUS)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

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
	@git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42

.PHONY:  clean libmlx install