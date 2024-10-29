/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:57:42 by messkely          #+#    #+#             */
/*   Updated: 2024/10/29 12:03:26 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../mlx/include/MLX42/MLX42.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

// Parssing

typedef struct s_flg
{
	int	N_flg;
	int	S_flg;
	int	W_flg;
	int	E_flg;
	int	F_flg;
	int	C_flg;
}	t_flg;

typedef struct s_map
{
	char		**map3D;
	int			rows_size;
	char		*NOpath;
	char		*SOpath;
	char		*WEpath;
	char		*EApath;
	int			F[3];
	int			C[3];
	uint32_t	Fhex;
	uint32_t	Chex;
}	t_map;

// Rendring

typedef struct s_move_info
{
	double	new_x;
	double	new_y;
	double	new_angle;
	int		is_moving;
}	t_move_info;

typedef struct s_ray
{
	double	angle;
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	double	horz_intersect_x;
	double	horz_intersect_y;
	double	vert_intersect_x;
	double	vert_intersect_y;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		is_vertical_hit;
}	t_ray;

typedef struct s_data
{
	double		tile_size;
	int			rows;
	int			columns;
	double		map_width;
	double		map_height;
	double		screen_width;
	double		screen_height;
	double		fov;
	int			num_rays;
	uint32_t	F;
	uint32_t	C;
	char		**map;
	t_ray		*rays;
}	t_data;

typedef struct s_txtr
{
	mlx_texture_t	*wall_north;
	mlx_texture_t	*wall_west;
	mlx_texture_t	*wall_south;
	mlx_texture_t	*wall_east;
}	t_txtr;

typedef struct s_img
{
	mlx_image_t	*frame;
	mlx_image_t	*wall_north;
	mlx_image_t	*wall_west;
	mlx_image_t	*wall_south;
	mlx_image_t	*wall_east;
	mlx_image_t	**sprint_imgs;
	mlx_image_t	**stop_imgs;
}	t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
	uint32_t	color;
	int			radius;
	double		move_step;
	double		rotation_step;
}	t_player;

typedef struct s_mlx
{
	int			stop;
	t_data		data;
	mlx_t		*ptr;
	t_txtr		txtrs;
	t_img		imgs;
	t_map		map;
	t_player	player;
}	t_mlx;

//parssing

void	ft_error(char *s);
void	init_flg(t_flg *flg);
int		check(char *str, char *to_find);
int		ft_strlen(char *s);
char	**ft_split(t_map *my_map, char *s, char c);
char	*ft_trim(char *s);
int		ft_isdigit(char c);
int		is_num(char *s);
long	ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strjoin(char *dir, char *src, char *extension);

char	*check_file_elementes(t_map *my_map, char *file);
void	check_walls(t_map *map, char **map3D);
void	process_file_content(char *map_path, t_map *my_map);
void	convert_RGB_to_hex(t_map *map, int color_buff[3], char c);

// Rendring
mlx_image_t **ft_load_image(t_mlx *mlx, int num_sprites);
void render_imgs(t_mlx *mlx, mlx_image_t **sprites, int n_sprite);
void animation(t_mlx *mlx, mlx_image_t **sprites, int n_sprite);
// void	free_game(t_mlx *mlx, t_map *map);
void	free_game(t_map *map);

#endif