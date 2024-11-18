/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:47:14 by yiken             #+#    #+#             */
/*   Updated: 2024/11/17 17:28:35 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_flg
{
	int	N_flg;
	int	S_flg;
	int	W_flg;
	int	E_flg;
	int	F_flg;
	int	C_flg;
	int	break_flg;
}	t_flg;

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
	char		**map;
	t_ray		*rays;
	uint32_t	ceiling_color;
	uint32_t	floor_color;
	char		*wall_no_path;
	char		*wall_we_path;
	char		*wall_so_path;
	char		*wall_ea_path;
	int			*ceiling_rgb_buf; // added
	int			*floor_rgb_buf; // added
	t_flg		*flg; // added
}	t_data;

typedef struct s_txtrs
{
	mlx_texture_t	*wall_north;
	mlx_texture_t	*wall_west;
	mlx_texture_t	*wall_south;
	mlx_texture_t	*wall_east;
}	t_txtrs;

typedef struct s_imgs
{
	mlx_image_t	*frame;
	mlx_image_t	*wall_north;
	mlx_image_t	*wall_west;
	mlx_image_t	*wall_south;
	mlx_image_t	*wall_east;
}	t_imgs;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
	double		new_angle;
	int			radius;
	double		move_step;
	double		rotation_step;
	int			is_moving;
	uint32_t	color;
	int			big_step;
}	t_player;

typedef struct s_mlx
{
	t_data		data;
	mlx_t		*ptr;
	t_txtrs		txtrs;
	t_imgs		imgs;
	t_player	player;
}	t_mlx;

// graphics

void	init_cub3d(t_mlx *mlx);
void	update_player_on_keypress(t_mlx *mlx);
void	draw_2d_map(t_mlx *mlx);
void	draw_3d_map(t_mlx *mlx);
void	cast_rays(t_mlx *mlx);
void	graceful_exit(t_mlx *mlx, int code);

// parser

void	ft_error(char *s);
void	init_flg(t_flg *flg);
int		check(char *str, char *to_find);
int		ft_strlen(char *s);
char	*ft_trim(char *s);
int		ft_isdigit(char c);
int		is_num(char *s);
long	ft_atoi(const char *str);
char	*get_line(char *s, char c);
int		go_back(char *file, int i);
int		*create_rgb_buf();
char	**ft_split(t_data *data, char *s, char c);

char	*check_file_elementes(t_data *data, char *file, t_flg *flg);
void	check_walls(t_data *data, char **map);
void	process_config_file(t_mlx *mlx, char *map_path, t_data *data);
void	increasing_flg(t_flg *flg, char vector);
void	check_flags(t_flg *flg);
void	free_game(t_data *data);

#endif