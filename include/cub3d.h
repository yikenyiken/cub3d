/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:57:42 by messkely          #+#    #+#             */
/*   Updated: 2024/11/12 09:03:11 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
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
	double		map_width;
	double		map_height;
	double		screen_width;
	double		screen_height;
	double		fov;
	double		player_angle;
	int			rows;
	int			columns;
	int			max_width;
	int			max_height;
	int			num_rays;
	int			hero_frames;
	int			F[3];
	int			C[3];
	int			player_pos[2];
	char		**map;
	char		*wall_no_path;
	char		*wall_we_path;
	char		*wall_so_path;
	char		*wall_ea_path;
	uint32_t	ceiling_color;
	uint32_t	floor_color;
	t_ray		*rays;
	t_flg		*flg;
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
	t_data		*data;
	mlx_t		*ptr;
	t_txtrs		txtrs;
	t_imgs		imgs;
	t_player	player;
	int			stop;
}	t_mlx;

//parssing

void	ft_error(char *s);
void	init_flg(t_flg *flg);
int		check(char *str, char *to_find);
int		ft_strlen(char *s);
char	*ft_trim(char *s);
int		ft_isdigit(char c);
int		is_num(char *s);
long	ft_atoi(const char *str);
char	*get_line(char *s, char c);
char	**ft_split(t_data *data, char *s, char c);

char	*check_file_elementes(t_data *data, char *file, t_flg *flg);
void	check_walls(t_data *data, char **map);
void	process_file_content(char *map_path, t_data *data);
void	increasing_flg(t_flg *flg, char vector);
void	check_flags(t_flg *flg);
void	free_game(t_data *data);

// Rendring
void	init_cub3d(t_mlx *mlx, t_data *data);
void	update_player_on_keypress(t_mlx *mlx);
void	draw_2d_map(t_mlx *mlx);
void	draw_3d_map(t_mlx *mlx);
void	cast_rays(t_mlx *mlx);
void	graceful_exit(t_mlx *mlx, int code);

#endif