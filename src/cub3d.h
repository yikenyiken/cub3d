/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:47:14 by yiken             #+#    #+#             */
/*   Updated: 2024/10/20 17:47:24 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

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
	double	tile_size;
	int		rows;
	int		columns;
	double	map_width;
	double	map_height;
	double	screen_width;
	double	screen_height;
	double	fov;
	int		num_rays;
	char	**map;
	t_ray	*rays;
}	t_data;

typedef struct s_img
{
	mlx_image_t	*frame;
	mlx_image_t	*wall;
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
	t_data		*data;
	mlx_t		*ptr;
	t_img		img;
	t_player	player;
}	t_mlx;

#endif