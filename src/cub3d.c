/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:52:35 by yiken             #+#    #+#             */
/*   Updated: 2024/10/22 12:27:33 by yiken            ###   ########.fr       */
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

void	graceful_exit(t_mlx *mlx)
{
	free(mlx->data->rays);
	mlx_terminate(mlx->ptr); // this function includes all previously created images in the cleanup process
	exit(1);
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
	int	u_size;

	u_size = 128;
	data->map = map;
	data->rows = 10;
	data->columns = 15;
	data->fov = 60 * (M_PI / 180);
	data->screen_width = u_size * data->columns;
	data->screen_height = u_size * data->rows;
	data->tile_size = 24;
	data->map_width = data->tile_size * data->columns;
	data->map_height = data->tile_size * data->rows;
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
	set_player_xy(player, data->map_width / 2, data->map_height / 2);

	player->angle = M_PI;
	player->color = 0xFF0000FF;
	player->radius = 4;
	player->move_step = 1;
	player->rotation_step = 1.30 * (M_PI / 180);
}

void	load_textures(t_mlx *mlx)
{
	t_txtr	*txtr;

	txtr = &mlx->txtr;

	txtr->wall_north = mlx_load_png("textures/wall_north.png");
	if (!txtr->wall_north)
		graceful_exit(mlx);
	printf("failed\n");

	txtr->wall_west = mlx_load_png("textures/wall_west.png");
	if (!txtr->wall_west)
		(mlx_delete_texture(txtr->wall_north), graceful_exit(mlx));
	
	txtr->wall_south = mlx_load_png("textures/wall_south.png");
	if (!txtr->wall_south)
		(mlx_delete_texture(txtr->wall_north), mlx_delete_texture(txtr->wall_west), graceful_exit(mlx));

	txtr->wall_east = mlx_load_png("textures/wall_east.png");
	if (!txtr->wall_east)
		(mlx_delete_texture(txtr->wall_north), mlx_delete_texture(txtr->wall_west)
			, mlx_delete_texture(txtr->wall_south), graceful_exit(mlx));
}

void	delete_txtrs(t_txtr *txtr)
{
	mlx_delete_texture(txtr->wall_north);
	mlx_delete_texture(txtr->wall_west);
	mlx_delete_texture(txtr->wall_south);
	mlx_delete_texture(txtr->wall_east);
}

void	resize_imgs(t_mlx *mlx, t_img *img, double nwidth, double nheight)
{
	if (!mlx_resize_image(img->wall_north, nwidth, nheight)
		|| !mlx_resize_image(img->wall_west, nwidth, nheight)
			|| !mlx_resize_image(img->wall_south, nwidth, nheight)
				|| !mlx_resize_image(img->wall_east, nwidth, nheight))
		graceful_exit(mlx);
}

void	check_img_valid(t_mlx *mlx, t_img *img)
{
	if (!img->wall_north || !img->wall_west
		|| !img->wall_south || !img->wall_east)
		graceful_exit(mlx);
}

void	load_images(t_mlx *mlx, t_data *data)
{
	t_txtr	*txtr;
	t_img	*img;

	txtr = &mlx->txtr;
	img = &mlx->img;

	img->frame = mlx_new_image(mlx->ptr, data->screen_width, data->screen_height);
	if (!img->frame)
		graceful_exit(mlx);

	img->wall_north = mlx_texture_to_image(mlx->ptr, txtr->wall_north);

	img->wall_west = mlx_texture_to_image(mlx->ptr, txtr->wall_west);

	img->wall_south = mlx_texture_to_image(mlx->ptr, txtr->wall_south);

	img->wall_east = mlx_texture_to_image(mlx->ptr, txtr->wall_east);

	delete_txtrs(txtr);
	check_img_valid(mlx, img);
	resize_imgs(mlx, img, data->tile_size, data->tile_size);
}

void	render_frame_img(t_mlx *mlx)
{
	if (mlx_image_to_window(mlx->ptr, mlx->img.frame, 0, 0) == -1)
		graceful_exit(mlx);
}

void	create_window(t_mlx *mlx, t_data *data)
{
	mlx->ptr = mlx_init(data->screen_width, data->screen_height, "cub3D", 0);
	if (!mlx->ptr)
		free(data->rays), exit(1);
}

void	init(t_mlx *mlx, t_data *data, char **map)
{
	mlx->data = data;
	init_data(data, map);
	init_player(&mlx->player, data);
	create_window(mlx, data);
	load_textures(mlx);
	load_images(mlx, data);
	render_frame_img(mlx);
}

int	is_wall_hit(t_mlx *mlx, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = x / mlx->data->tile_size;
	map_y = y / mlx->data->tile_size;
	return (mlx->data->map[map_y][map_x] - '0');
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	init_info(t_move_info *info, t_mlx *mlx)
{
	info->new_x = mlx->player.x;
	info->new_y = mlx->player.y;
	info->new_angle = mlx->player.angle;
	info->is_moving = 0;
}

void	vertical_info(t_mlx *mlx, t_move_info *info)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_W)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_A)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_D)))
		info->is_moving = 1;

	if (mlx_is_key_down(mlx->ptr, MLX_KEY_S)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_A)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_D)))
	{
		info->new_angle += M_PI;
		info->is_moving = 1;
	}
}

void	horizontal_info(t_mlx *mlx, t_move_info *info)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_D)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_W)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_S)))
	{
		info->new_angle += M_PI / 2;
		info->is_moving = 1;
	}

	if (mlx_is_key_down(mlx->ptr, MLX_KEY_A)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_W)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_S)))
	{
		info->new_angle -= M_PI / 2;
		info->is_moving = 1;
	}
}

void	upwards_diagonal_info(t_mlx *mlx, t_move_info *info)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_W) &&
		mlx_is_key_down(mlx->ptr, MLX_KEY_D))
	{
		info->new_angle += (M_PI / 2) / 2;
		info->is_moving = 1;
	}
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_W) &&
		mlx_is_key_down(mlx->ptr, MLX_KEY_A))
	{
		info->new_angle -= (M_PI / 2) / 2;
		info->is_moving = 1;
	}
}

void	downwards_diagonal_info(t_mlx *mlx, t_move_info *info)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_S) &&
		mlx_is_key_down(mlx->ptr, MLX_KEY_D))
	{
		info->new_angle += M_PI - (M_PI / 2 / 2);
		info->is_moving = 1;
	}
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_S) &&
		mlx_is_key_down(mlx->ptr, MLX_KEY_A))
	{
		info->new_angle += M_PI + (M_PI / 2 / 2);
		info->is_moving = 1;
	}
}

void	rotate(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_RIGHT))
		mlx->player.angle += mlx->player.rotation_step;
	else if (mlx_is_key_down(mlx->ptr, MLX_KEY_LEFT))
		mlx->player.angle -= mlx->player.rotation_step;
}

void	move_by_info(t_mlx *mlx, t_move_info *info)
{
	double	x_ahead;
	double	y_ahead;
	double	pixels_ahead;

	pixels_ahead = 6;
	
	if (!info->is_moving)
		return ;
	
	info->new_x += cos(info->new_angle) * mlx->player.move_step;
	info->new_y += sin(info->new_angle) * mlx->player.move_step;
	
	x_ahead = info->new_x + cos(info->new_angle) * pixels_ahead;
	y_ahead = info->new_y + sin(info->new_angle) * pixels_ahead;
	
	if (!is_wall_hit(mlx, x_ahead, y_ahead))
	{
		mlx->player.x = info->new_x;
		mlx->player.y = info->new_y;
	}
}

void	game_exit(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_ESCAPE))
		graceful_exit(mlx);
}

void	update_player(t_mlx *mlx)
{
	t_move_info	info;

	rotate(mlx);

	init_info(&info, mlx);

	vertical_info(mlx, &info);
	horizontal_info(mlx, &info);

	upwards_diagonal_info(mlx, &info);
	downwards_diagonal_info(mlx, &info);

	move_by_info(mlx, &info);

	game_exit(mlx);
}

void	set_horz_intersect_xy(t_ray *ray, double ray_angle, t_mlx *mlx)
{

	int 	ray_facing_up;

	ray_facing_up = ray_angle > M_PI;
	ray->horz_intersect_x = ray->x_intercept;
	ray->horz_intersect_y = ray->y_intercept;

	while ((ray->horz_intersect_x >= (double)0 && ray->horz_intersect_x <= mlx->data->map_width)
		&& (ray->horz_intersect_y >= (double)0 && ray->horz_intersect_y <= mlx->data->map_height))
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

	ray->y_intercept = floor(mlx->player.y / mlx->data->tile_size) * mlx->data->tile_size;
	if (!ray_facing_up)
		ray->y_intercept += mlx->data->tile_size;

	ray->x_intercept = mlx->player.x + (ray->y_intercept - mlx->player.y) / tan(ray_angle);

	ray->y_step = mlx->data->tile_size;
	if (ray_facing_up)
		ray->y_step = -ray->y_step;
	
	ray->x_step = mlx->data->tile_size / tan(ray_angle);
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

	while ((ray->vert_intersect_x >= (double)0 && ray->vert_intersect_x <= mlx->data->map_width)
		&& (ray->vert_intersect_y >= (double)0 && ray->vert_intersect_y <= mlx->data->map_height))
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

	ray->x_intercept = floor(mlx->player.x / mlx->data->tile_size) * mlx->data->tile_size;
	if (ray_facing_right)
		ray->x_intercept += mlx->data->tile_size;

	ray->y_intercept = mlx->player.y + (ray->x_intercept - mlx->player.x) * tan(ray_angle);

	ray->x_step = mlx->data->tile_size;
	if (!ray_facing_right)
		ray->x_step = -ray->x_step;

	ray->y_step = mlx->data->tile_size * tan(ray_angle);
	if (!ray_facing_up && ray->y_step < 0)
		ray->y_step = -ray->y_step;
	if (ray_facing_up && ray->y_step > 0)
		ray->y_step = -ray->y_step;
	set_vert_intersect_xy(ray, ray_angle, mlx);
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))); // this formula is used to calculate the hypothenuse length of a triangle using the length of the other two sides
}

void	set_ray_distance(t_ray *ray, t_mlx *mlx)
{
	double	horz_distance;
	double	vert_distance;

	horz_distance = distance_between_points(mlx->player.x, mlx->player.y, ray->horz_intersect_x, ray->horz_intersect_y);
	vert_distance = distance_between_points(mlx->player.x, mlx->player.y, ray->vert_intersect_x, ray->vert_intersect_y);
	ray->distance = horz_distance;
	ray->wall_hit_x = ray->horz_intersect_x;
	ray->wall_hit_y = ray->horz_intersect_y;
	ray->is_vertical_hit = 0;
	if (horz_distance > vert_distance)
	{
		ray->wall_hit_x = ray->vert_intersect_x;
		ray->wall_hit_y = ray->vert_intersect_y;
		ray->distance = vert_distance;
		ray->is_vertical_hit = 1;
	}
}

void	cast_ray(t_ray *ray, t_mlx *mlx)
{
	find_horz_intersection(ray, ray->angle, mlx);
	find_vert_intersection(ray, ray->angle, mlx);
	set_ray_distance(ray, mlx);
	// the steps that are taken to find the horizontal/vertical intersection are as follows:
		// calculate the x_intercept (check code)
		// calculate the y_intercept (check code)
		// calculate the x_step (check code)
		// calculate the y_step (check code)
		// increment x_intercept by x_step & y_intercept by y_step until a wall is hit
		// ps: x_step & y_step can be negative depending on the direction the ray is facing
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
	while (i < y + mlx->data->tile_size)
	{
		j = x;
		while (j < x + mlx->data->tile_size)
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
			draw_map_tile(j * mlx->data->tile_size, i * mlx->data->tile_size, mlx, color);
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

uint8_t	*get_img_pxbuf(t_ray *ray, t_player *player, t_img *img)
{
	if (ray->is_vertical_hit && ray->wall_hit_x > player->x) // east
		return (img->wall_east->pixels);
	if (ray->is_vertical_hit && ray->wall_hit_x < player->x) // west
		return (img->wall_west->pixels);
	if (!ray->is_vertical_hit && ray->wall_hit_y > player->y) // south
		return (img->wall_south->pixels);

	return (img->wall_north->pixels); // north
}

void	draw_wall(t_mlx *mlx, int x, double y, double wall_strip_height)
{
	int			i;
	int			textureX;
	int			textureY;
	uint32_t	color;
	uint32_t	*color_buffer;

	color_buffer = (uint32_t *)get_img_pxbuf(mlx->data->rays + x, &mlx->player, &mlx->img);
	textureX = (int)(mlx->data->rays + x)->wall_hit_x % (int)mlx->data->tile_size;
	if ((mlx->data->rays + x)->is_vertical_hit)
		textureX = (int)(mlx->data->rays + x)->wall_hit_y % (int)mlx->data->tile_size;
	i = y;
	if (i < 0)
		i = 0;
	while (i < (int)(y + wall_strip_height) && i < (int)mlx->data->screen_height)
	{
		textureY = (i - (int)y) * (mlx->data->tile_size / wall_strip_height);
		if (textureY > mlx->data->tile_size)
			break;
		color = color_buffer[(textureY * (int)mlx->data->tile_size) + textureX];
		mlx_put_pixel(mlx->img.frame, x, i++, color);
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
		wall_strip_height = (mlx->data->tile_size / perp_distance) * distance_projection_plane;
		draw_wall(mlx, i, (mlx->data->screen_height / 2) - (wall_strip_height / 2), wall_strip_height);
		i++;
	}
}

void	draw_ceiling_floor(t_mlx *mlx)
{
	uint32_t	*color_buffer;
	uint32_t 	ceiling_color = 0x65FBF1FF; //cloudy sky color
	uint32_t 	floor_color = 0x5511FFFF; //grass color
	uint32_t	i;
	uint32_t	j;

	color_buffer = (uint32_t *)mlx->img.frame->pixels;
	i = 0;
	//draw ceiling pixels
	while (i < mlx->img.frame->height / 2)
	{
		j = 0;
		while (j < mlx->img.frame->width)
			*(color_buffer + (i * mlx->img.frame->width) + j++) = ceiling_color; // (i * mlx.img.frame->width) is used to travel to the next row
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
	draw_ceiling_floor(mlx);
	draw_walls(mlx);
	draw_map(mlx);
	draw_rays(mlx);
	draw_player(mlx);
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
	graceful_exit(&mlx);
}

// what is it to be done
	// what is it that makes wall_north not appear
		// is it that the buffer still holds the old pixels
		// is it that the size of it is pretty big
	// render different textures based on the cardinal directions
		// vertically intersecting ray means it is drawing what's on the sides // seems so
		// horizontally intersecting ray means it is drawing what's in front or back
		// in case of vertical intersection
			// if wall_hit_x is smaller than (mini_map_width / 2) it means we are dealing with west
			// if wall_hit_x is greater than (mini_map_width / 2) it means we are dealing with east
		// in case of horizontal intersection
			// if wall_hit_y is smallter than (mini_map_height / 2) it means we are dealing with north
			// if wall_hit_y is greater than (mini_map_height / 2) it means we are dealing with south

// function name: pick img