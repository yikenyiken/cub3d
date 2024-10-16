/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:52:35 by yiken             #+#    #+#             */
/*   Updated: 2024/10/16 13:40:34 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/include/MLX42/MLX42.h"
#include <stdio.h>
#include <string.h>
#include "cub3d.h"

void	put_err(char *str)
{
	while (*str)
		write(2, str++, 1);
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

t_ray	*create_rays(t_data *data)
{
	t_ray	*rays;

	rays = malloc(sizeof(t_ray) * data->num_rays);
	if (!rays)
		put_err("failed to allocate rays\n"), exit(1);
	return (rays);
}

void	init_data(t_data *data, char **map)
{
	int	screen_max_width;
	int	screen_max_height;

	data->map = map;
	screen_max_width = 1024;
	screen_max_height = 720;
	data->screen_tile_size = 128;
	data->rows = 10;
	data->columns = 15;
	data->fov = 60 * (M_PI / 180);
	data->screen_width = data->screen_tile_size * data->columns;
	data->screen_height = data->screen_tile_size * data->rows;
	// if (data->screen_height > screen_max_height || data->screen_width > screen_max_width)
	// 	(put_err("too large map\n"), exit(1));
	data->mini_map_tile_size = 24;
	data->mini_map_width = data->mini_map_tile_size * data->columns;
	data->mini_map_height = data->mini_map_tile_size * data->rows;
	data->num_rays = data->screen_width;
	data->rays = create_rays(data);
}

void	set_player_xy(t_player *player, double x, double y)
{
	player->x = x;
	player->y = y;
}

void	init_player(t_player *player, t_data *data)
{
	set_player_xy(player, data->mini_map_width / 2, data->mini_map_height / 2);

	player->angle = M_PI;
	player->color = 0xFF0000FF;
	player->radius = 4;
	player->move_step = 1;
	player->rotation_step = 2 * (M_PI / 180);
}

void	render_frame_img(t_mlx *mlx, t_data *data)
{
	mlx->img.frame = mlx_new_image(mlx->ptr, data->screen_width, data->screen_height);
	mlx_image_to_window(mlx->ptr, mlx->img.frame, 0, 0);
}

void	init(t_mlx *mlx, t_data *data, char **map)
{
	init_data(data, map);
	init_player(&mlx->player, data);
	mlx->ptr = mlx_init(data->screen_width, data->screen_height, "cub3D", 0);
	if (!mlx->ptr)
		exit(1);
	render_frame_img(mlx, data);
	mlx->data = data;
}

int	is_wall_hit(t_mlx *mlx, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = x / mlx->data->mini_map_tile_size;
	map_y = y / mlx->data->mini_map_tile_size;
	return (mlx->data->map[map_y][map_x] - '0');
}

void	update_player(t_mlx *mlx)
{
	int		move_direction;
	double	new_x;
	double	new_y;

	move_direction = 0;

	if (mlx_is_key_down(mlx->ptr, MLX_KEY_W))
		move_direction = 1;

    if (mlx_is_key_down(mlx->ptr, MLX_KEY_S))
		move_direction = -1;

    if (mlx_is_key_down(mlx->ptr, MLX_KEY_A))
		mlx->player.angle += -mlx->player.rotation_step;

    if (mlx_is_key_down(mlx->ptr, MLX_KEY_D))
		mlx->player.angle += mlx->player.rotation_step;
	
	new_x = mlx->player.x + cos(mlx->player.angle) * mlx->player.move_step * move_direction;
	new_y = mlx->player.y + sin(mlx->player.angle) * mlx->player.move_step * move_direction;

	if (!is_wall_hit(mlx, new_x, new_y))
		set_player_xy(&mlx->player, new_x, new_y);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	set_horz_intersect_xy(t_ray *ray, double ray_angle, t_mlx *mlx)
{

	int 	ray_facing_up;

	ray_facing_up = ray_angle > M_PI;
	ray->horz_intersect_x = ray->x_intercept;
	ray->horz_intersect_y = ray->y_intercept;

	while ((ray->horz_intersect_x >= (double)0 && ray->horz_intersect_x <= mlx->data->mini_map_width)
		&& (ray->horz_intersect_y >= (double)0 && ray->horz_intersect_y <= mlx->data->mini_map_height))
	{
		if (is_wall_hit(mlx, ray->horz_intersect_x, ray->horz_intersect_y - ray_facing_up))
			break ;
		ray->horz_intersect_x += ray->x_step;
		ray->horz_intersect_y += ray->y_step;
	}
}

void	find_horz_intersection(t_ray *ray, double ray_angle, t_mlx *mlx)
{
	int	ray_facing_up;
	int	ray_facing_right;

	ray_facing_up = ray_angle > M_PI;
	ray_facing_right = ray_angle < (M_PI / 2) || ray_angle > 3 * (M_PI / 2);

	ray->y_intercept = floor(mlx->player.y / mlx->data->mini_map_tile_size) * mlx->data->mini_map_tile_size;
	if (!ray_facing_up)
		ray->y_intercept += mlx->data->mini_map_tile_size;

	ray->x_intercept = mlx->player.x + (ray->y_intercept - mlx->player.y) / tan(ray_angle);

	ray->y_step = mlx->data->mini_map_tile_size;
	if (ray_facing_up)
		ray->y_step = -ray->y_step;
	
	ray->x_step = mlx->data->mini_map_tile_size / tan(ray_angle);
	if (ray_facing_right && ray->x_step < 0)
		ray->x_step = -ray->x_step;
	if (!ray_facing_right && ray->x_step > 0)
		ray->x_step = -ray->x_step;
	set_horz_intersect_xy(ray, ray_angle, mlx);
}

void	set_vert_intersect_xy(t_ray *ray, double ray_angle, t_mlx *mlx)
{
	int		ray_facing_right;

	ray_facing_right = ray_angle < (M_PI / 2) || ray_angle > 3 * (M_PI / 2);
	ray->vert_intersect_x = ray->x_intercept;
	ray->vert_intersect_y = ray->y_intercept;

	while ((ray->vert_intersect_x >= (double)0 && ray->vert_intersect_x <= mlx->data->mini_map_width)
		&& (ray->vert_intersect_y >= (double)0 && ray->vert_intersect_y <= mlx->data->mini_map_height))
	{
		if (is_wall_hit(mlx, ray->vert_intersect_x - !ray_facing_right, ray->vert_intersect_y))
			break ;
		ray->vert_intersect_x += ray->x_step;
		ray->vert_intersect_y += ray->y_step;
	}
}

void	find_vert_intersection(t_ray *ray, double ray_angle, t_mlx *mlx)
{
	int	ray_facing_up;
	int	ray_facing_right;

	ray_facing_up = ray_angle > M_PI;
	ray_facing_right = ray_angle < (M_PI / 2) || ray_angle > 3 * (M_PI / 2);

	ray->x_intercept = floor(mlx->player.x / mlx->data->mini_map_tile_size) * mlx->data->mini_map_tile_size;
	if (ray_facing_right)
		ray->x_intercept += mlx->data->mini_map_tile_size;

	ray->y_intercept = mlx->player.y + (ray->x_intercept - mlx->player.x) * tan(ray_angle);

	ray->x_step = mlx->data->mini_map_tile_size;
	if (!ray_facing_right)
		ray->x_step = -ray->x_step;

	ray->y_step = mlx->data->mini_map_tile_size * tan(ray_angle);
	if (!ray_facing_up && ray->y_step < 0)
		ray->y_step = -ray->y_step;
	if (ray_facing_up && ray->y_step > 0)
		ray->y_step = -ray->y_step;
	set_vert_intersect_xy(ray, ray_angle, mlx);
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_ray(t_ray *ray, t_mlx *mlx)
{
	double	horz_distance;
	double	vert_distance;

	find_horz_intersection(ray, ray->angle, mlx);
	find_vert_intersection(ray, ray->angle, mlx);
	horz_distance = distance_between_points(mlx->player.x, mlx->player.y, ray->horz_intersect_x, ray->horz_intersect_y);
	vert_distance = distance_between_points(mlx->player.x, mlx->player.y, ray->vert_intersect_x, ray->vert_intersect_y);
	ray->distance = horz_distance;
	ray->wall_hit_x = ray->horz_intersect_x;
	ray->wall_hit_y = ray->horz_intersect_y;
	if (horz_distance > vert_distance)
	{
		ray->wall_hit_x = ray->vert_intersect_x;
		ray->wall_hit_y = ray->vert_intersect_y;
		ray->distance = vert_distance;
	}
}

void	cast_rays(t_mlx *mlx)
{
	double	ray_angle;
	int			i;

	ray_angle = mlx->player.angle - (mlx->data->fov / 2); // since fov == 60deg, you want half of your fov
	//to the right of the direction you are looking at (player.angle), and let's consider the angle of the
	//first ray: player.angle - half of fov
	i = 0;
	while (i < mlx->data->num_rays)
	{
		(mlx->data->rays + i)->angle = normalize_angle(ray_angle);
		cast_ray(mlx->data->rays + i, mlx);
		ray_angle += mlx->data->fov / mlx->data->num_rays; // after fiding the angle of the first ray (ray_angle)
		//you want an increment by which you will advance to get the angle of the second ray (second_ray_angle),
		//at the same time you don't want to surpass fov 60deg so that ray_angle + (incerement * num_rays) == fov (60deg)
		i++;
	}
}

void	draw_map_tile(int x, int y, t_mlx *mlx, uint32_t color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + mlx->data->mini_map_tile_size)
	{
		j = x;
		while (j < x + mlx->data->mini_map_tile_size)
		{
			mlx_put_pixel(mlx->img.frame, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_mlx *mlx)
{
	char		**map;
	int			i;
	int			j;
	uint32_t	color;

	map = mlx->data->map;
	i = 0;
	while (i < mlx->data->rows)
	{
		j = 0;
		while (j < mlx->data->columns)
		{
			if (map[i][j] - '0')
				color = 0xFF555194;
			else
				color = 0xFFFFFFFF;
			draw_map_tile(j * mlx->data->mini_map_tile_size, i * mlx->data->mini_map_tile_size, mlx, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -(mlx->player.radius);
	while (y <= mlx->player.radius)
	{
		x = -(mlx->player.radius);
		while (x <= mlx->player.radius)
		{
			if (x * x + y * y <= mlx->player.radius * mlx->player.radius)
				mlx_put_pixel(mlx->img.frame, mlx->player.x + x, mlx->player.y + y, mlx->player.color);
			x++;
		}
		y++;
	}
}

// void	draw_player_dir(t_mlx *mlx)
// {
// 	double	x;
// 	double	y;
// 	int	scaler;

// 	scaler = 30;
// 	while (scaler)
// 	{
// 		x = mlx->player.x + cos(mlx->player.angle) * scaler;
// 		y = mlx->player.y + sin(mlx->player.angle) * scaler;
// 		mlx_put_pixel(mlx->img.frame, x, y, 0x0000FFFF);
// 		scaler--;
// 	}
// }

void	draw_ray(t_mlx *mlx, t_ray *ray)
{
	double	dx;
	double	dy;
	double	steps;
	double	x_inc;
	double	y_inc;
	int		i;

	dx = ray->wall_hit_x - mlx->player.x;
	dy = ray->wall_hit_y - mlx->player.y;
	steps = max(fabs(dx), fabs(dy));
	x_inc = dx / steps;
	y_inc = dy / steps;
	i = 0;
	while (i < round(steps))
	{
		int x = floor(mlx->player.x + (x_inc * i));
		int y = floor(mlx->player.y + (y_inc * i));
		mlx_put_pixel(mlx->img.frame, x, y, 0x00FF00FF);
		i++;
	}
}

void	draw_rays(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->data->num_rays)
	{
		draw_ray(mlx, mlx->data->rays + i);
		i++;
	}
}

void	draw_wall(t_mlx *mlx, int x, double y, double wall_strip_height)
{
	double	i;

	i = y;
	if (i < 0)
		i = 0;
	while (i < (int)(y + wall_strip_height) && i < mlx->data->screen_height)
	{
		mlx_put_pixel(mlx->img.frame, x, i, 0x99555194);
		i++;
	}
}

void	draw_walls(t_mlx *mlx)
{
	int		i;
	double	wall_strip_height;
	double	distance_projection_plane;
	double	perp_distance;
	t_ray	*ray;

	distance_projection_plane = (mlx->data->screen_width / 2) / tan(mlx->data->fov / 2);
	i = 0;
	while (i < mlx->data->num_rays)
	{
		ray = mlx->data->rays + i;
		perp_distance = ray->distance * cos(ray->angle - mlx->player.angle);
		wall_strip_height = (mlx->data->mini_map_tile_size / perp_distance) * distance_projection_plane;
		draw_wall(mlx, i, (int)(mlx->data->screen_height / 2) - (wall_strip_height / 2), wall_strip_height);
		i++;
	}
}

void	draw_ceiling_floor_color(t_mlx *mlx)
{
	uint32_t	*color_buffer;
	uint32_t 	ceiling_color = 0x65FBF1FF; //cloudy sky color
	uint32_t 	floor_color = 0x5511FFFF; //grass color
	uint32_t	i;
	uint32_t	j;

	i = 0;
	color_buffer = (uint32_t *)mlx->img.frame->pixels;
	//draw ceiling pixels
	while (i < mlx->img.frame->height / 2)
	{
		j = 0;
		while (j < mlx->img.frame->width)
			*(color_buffer + (i * mlx->img.frame->width) + j++) = ceiling_color;
		i++;
	}
	//draw floor pixels
	i = mlx->img.frame->height / 2;
	while (i < mlx->img.frame->height)
	{
		j = 0;
		while (j < mlx->img.frame->width)
			*(color_buffer + (i * mlx->img.frame->width) + j++) = floor_color;
		i++;
	}
}

void	update_frame(t_mlx *mlx)
{
	draw_ceiling_floor_color(mlx);
	draw_walls(mlx);
	draw_map(mlx);
	draw_rays(mlx);
	draw_player(mlx);
	// draw_player_dir(mlx);
}

void	game_loop(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	update_player(mlx);
	cast_rays(mlx);
	update_frame(mlx);
}

int	main(void)
{
	t_data	data;
	t_mlx	mlx;
	char	*map[10] = {
		"111111111111111",
		"100000000000001",
		"100000001110001",
		"100000001000001",
		"100000000000001",
		"101000000000001",
		"101001111110001",
		"101000000000001",
		"100000000000001",
		"111111111111111",
	};

	init(&mlx, &data, map);
	mlx_loop_hook(mlx.ptr, game_loop, &mlx);
	mlx_loop(mlx.ptr);
	mlx_terminate(mlx.ptr);
}
