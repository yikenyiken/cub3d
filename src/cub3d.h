/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:47:14 by yiken             #+#    #+#             */
/*   Updated: 2024/10/06 13:02:09 by yiken            ###   ########.fr       */
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
	int		ray_facing_up;
	int		ray_facing_right;
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
}	t_ray;

typedef struct s_data
{
	int		tile_size;
	int		rows;
	int		columns;
	double	width;
	double	height;
	double	fov;
	int		num_rays;
	char	**map;
	t_ray	*rays;
}	t_data;

typedef struct s_img
{
	mlx_image_t	*frame;
}	t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
	uint32_t	color;
	int			radius;
}	t_player;

typedef struct s_mlx
{
	t_data		*data;
	mlx_t		*ptr;
	t_img		img;
	t_player	player;
}	t_mlx;

#endif