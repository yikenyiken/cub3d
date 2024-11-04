/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:52:35 by yiken             #+#    #+#             */
/*   Updated: 2024/10/29 13:01:29 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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
	free(mlx->data.rays);
	// mlx_delete_image(mlx->ptr, mlx->imgs.wall_east);
	// mlx_delete_image(mlx->ptr, mlx->imgs.wall_north);
	// mlx_delete_image(mlx->ptr, mlx->imgs.wall_south);
	// mlx_delete_image(mlx->ptr, mlx->imgs.wall_west);
	// int i = 0;
	// while (mlx->imgs.sprint_imgs[i])
	// 	mlx_delete_image(mlx->ptr, mlx->imgs.sprint_imgs[i]);
	free(mlx->imgs.sprint_imgs);
	mlx_terminate(mlx->ptr); // this function includes all previously created images in the cleanup process
}

t_ray	*create_rays(t_data *data)
{
	t_ray	*rays;

	rays = malloc(sizeof(t_ray) * data->num_rays);
	if (!rays)
		put_err("failed to allocate rays\n"), exit(1);
	return (rays);
}

void	init_data(t_data *data, t_map *map)
{
	const int		screen_tile_size = 128;
	
	data->map = map->map3D;
	data->F = map->Fhex;
	data->C = map->Chex;
	data->rows = 10;
	data->columns = 15;
	data->fov = 60 * (M_PI / 180);
	data->screen_width = screen_tile_size * data->columns;
	data->screen_height = screen_tile_size * data->rows;
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
	player->move_step = 2;
	player->rotation_step = 3 * (M_PI / 180);
}

void	create_window(t_mlx *mlx)
{
	mlx->ptr = mlx_init(mlx->data.screen_width, mlx->data.screen_height, "cub3D", 0);
	if (!mlx->ptr)
		free(mlx->data.rays), exit(1);
}

void	load_textures(t_mlx *mlx, t_map *map)
{
	t_txtr	*txtrs;

	txtrs = &mlx->txtrs;

	txtrs->wall_north = mlx_load_png(map->NOpath);
	if (!txtrs->wall_north)
		graceful_exit(mlx);

	txtrs->wall_west = mlx_load_png(map->WEpath);
	if (!txtrs->wall_west)
		(mlx_delete_texture(txtrs->wall_north), graceful_exit(mlx));

	txtrs->wall_south = mlx_load_png(map->SOpath);
	if (!txtrs->wall_south)
		(mlx_delete_texture(txtrs->wall_north), mlx_delete_texture(txtrs->wall_west), graceful_exit(mlx));

	txtrs->wall_east = mlx_load_png(map->EApath);
	if (!txtrs->wall_east)
		(mlx_delete_texture(txtrs->wall_north), mlx_delete_texture(txtrs->wall_west)
			, mlx_delete_texture(txtrs->wall_south), graceful_exit(mlx));
}

void	delete_txtrs(t_txtr *txtrs)
{
	mlx_delete_texture(txtrs->wall_north);
	mlx_delete_texture(txtrs->wall_west);
	mlx_delete_texture(txtrs->wall_south);
	mlx_delete_texture(txtrs->wall_east);
}

void	handle_txtr_to_img_fail(t_mlx *mlx, t_img *imgs)
{
	if (!imgs->wall_north || !imgs->wall_west
		|| !imgs->wall_south || !imgs->wall_east || !imgs->frame)
		graceful_exit(mlx);
}

void	resize_imgs(t_mlx *mlx, t_img *imgs, int nwidth, int nheight)
{
	if (!mlx_resize_image(imgs->wall_north, nwidth, nheight)
		|| !mlx_resize_image(imgs->wall_west, nwidth, nheight)
			|| !mlx_resize_image(imgs->wall_south, nwidth, nheight)
				|| !mlx_resize_image(imgs->wall_east, nwidth, nheight))
		graceful_exit(mlx);
}

void	load_images(t_mlx *mlx)
{
	t_txtr	*txtrs;
	t_img	*imgs;
	int		tile_size;

	txtrs = &mlx->txtrs;
	imgs = &mlx->imgs;
	tile_size = mlx->data.tile_size;

	imgs->frame = mlx_new_image(mlx->ptr, mlx->data.screen_width, mlx->data.screen_height);

	imgs->wall_north = mlx_texture_to_image(mlx->ptr, txtrs->wall_north);

	imgs->wall_west = mlx_texture_to_image(mlx->ptr, txtrs->wall_west);

	imgs->wall_south = mlx_texture_to_image(mlx->ptr, txtrs->wall_south);

	imgs->wall_east = mlx_texture_to_image(mlx->ptr, txtrs->wall_east);

	imgs->sprint_imgs = ft_load_image(mlx, 14);

	delete_txtrs(txtrs);
	handle_txtr_to_img_fail(mlx, imgs);
	resize_imgs(mlx, imgs, tile_size, tile_size);
}

void	render_frame_to_window(t_mlx *mlx)
{
	if (mlx_image_to_window(mlx->ptr, mlx->imgs.frame, 0, 0) == -1)
		graceful_exit(mlx);
}

void	init_mlx(t_mlx *mlx, t_map *map)
{
	mlx->stop = 0;
	create_window(mlx);
	load_textures(mlx, map);
	load_images(mlx);
	render_frame_to_window(mlx);
}

void	init_cub3d(t_mlx *mlx, t_map *map)
{
	init_data(&mlx->data, map);
	init_player(&mlx->player, &mlx->data);
	init_mlx(mlx, map);
}

int	is_wall_hit(t_mlx *mlx, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = x / mlx->data.tile_size;
	map_y = y / mlx->data.tile_size;
	return (mlx->data.map[map_y][map_x] - '0');
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	init_move_info(t_move_info *info, t_mlx *mlx)
{
	info->new_x = mlx->player.x;
	info->new_y = mlx->player.y;
	info->new_angle = mlx->player.angle;
	info->is_moving = 0;
}

void	vertical_move_listen(t_mlx *mlx, t_move_info *move_info)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_W)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_A)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_D)))
		(move_info->is_moving = 1, animation(mlx, mlx->imgs.sprint_imgs, 14));

	if (mlx_is_key_down(mlx->ptr, MLX_KEY_S)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_A)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_D)))
	{
		animation(mlx, mlx->imgs.sprint_imgs, 14);
		move_info->new_angle += M_PI;
		move_info->is_moving = 1;
	}
	
	if (!mlx_is_key_down(mlx->ptr, MLX_KEY_W)
		&& !mlx_is_key_down(mlx->ptr, MLX_KEY_S)
			&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_A)
				&& !mlx_is_key_down(mlx->ptr, MLX_KEY_D)))
	{
		mlx->stop = 0;
		for (int i = 1; i < 14; i++)
			mlx->imgs.sprint_imgs[i]->enabled = 0;
	}
		
}

void	hoizontal_move_listen(t_mlx *mlx, t_move_info *move_info)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_D)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_W)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_S)))
	{
		move_info->new_angle += M_PI / 2;
		move_info->is_moving = 1;
	}

	if (mlx_is_key_down(mlx->ptr, MLX_KEY_A)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_W)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_S)))
	{
		move_info->new_angle -= M_PI / 2;
		move_info->is_moving = 1;
	}
}

void	upwards_diagonal_move_listen(t_mlx *mlx, t_move_info *move_info)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_W) &&
		mlx_is_key_down(mlx->ptr, MLX_KEY_D))
	{
		move_info->new_angle += (M_PI / 2) / 2;
		move_info->is_moving = 1;
	}
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_W) &&
		mlx_is_key_down(mlx->ptr, MLX_KEY_A))
	{
		move_info->new_angle -= (M_PI / 2) / 2;
		move_info->is_moving = 1;
	}
}

void	downwards_diagonal_move_listen(t_mlx *mlx, t_move_info *move_info)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_S) &&
		mlx_is_key_down(mlx->ptr, MLX_KEY_D))
	{
		move_info->new_angle += M_PI - (M_PI / 2 / 2);
		move_info->is_moving = 1;
	}
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_S) &&
		mlx_is_key_down(mlx->ptr, MLX_KEY_A))
	{
		move_info->new_angle += M_PI + (M_PI / 2 / 2);
		move_info->is_moving = 1;
	}
}

void	player_rotation_listen(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_RIGHT))
		mlx->player.angle += mlx->player.rotation_step;
	else if (mlx_is_key_down(mlx->ptr, MLX_KEY_LEFT))
		mlx->player.angle -= mlx->player.rotation_step;
}

void	update_player_by_info(t_mlx *mlx, t_move_info *move_info)
{
	double	x_ahead;
	double	y_ahead;
	double	pixels_ahead;

	pixels_ahead = 6;
	
	if (!move_info->is_moving)
		return ;
	
	move_info->new_x += cos(move_info->new_angle) * mlx->player.move_step;
	move_info->new_y += sin(move_info->new_angle) * mlx->player.move_step;
	
	x_ahead = move_info->new_x + cos(move_info->new_angle) * pixels_ahead;
	y_ahead = move_info->new_y + sin(move_info->new_angle) * pixels_ahead;
	
	if (!is_wall_hit(mlx, x_ahead, y_ahead))
	{
		mlx->player.x = move_info->new_x;
		mlx->player.y = move_info->new_y;
	}
}

void	game_exit_listen(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_ESCAPE))
		graceful_exit(mlx);
}

void	update_player_on_keypress(t_mlx *mlx)
{
	t_move_info	move_info;

	init_move_info(&move_info, mlx);

	player_rotation_listen(mlx);

	vertical_move_listen(mlx, &move_info);
	hoizontal_move_listen(mlx, &move_info);

	upwards_diagonal_move_listen(mlx, &move_info);
	downwards_diagonal_move_listen(mlx, &move_info);

	update_player_by_info(mlx, &move_info);

	game_exit_listen(mlx);
}

void	set_horz_intersect_xy(t_ray *ray, double ray_angle, t_mlx *mlx)
{

	int 	ray_facing_up;

	ray_facing_up = ray_angle > M_PI;
	ray->horz_intersect_x = ray->x_intercept;
	ray->horz_intersect_y = ray->y_intercept;

	while ((ray->horz_intersect_x >= (double)0 && ray->horz_intersect_x <= mlx->data.map_width)
		&& (ray->horz_intersect_y >= (double)0 && ray->horz_intersect_y <= mlx->data.map_height))
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

	ray->y_intercept = floor(mlx->player.y / mlx->data.tile_size) * mlx->data.tile_size;
	if (!ray_facing_up)
		ray->y_intercept += mlx->data.tile_size;

	ray->x_intercept = mlx->player.x + (ray->y_intercept - mlx->player.y) / tan(ray_angle);

	ray->y_step = mlx->data.tile_size;
	if (ray_facing_up)
		ray->y_step = -ray->y_step;
	
	ray->x_step = mlx->data.tile_size / tan(ray_angle);
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

	while ((ray->vert_intersect_x >= (double)0 && ray->vert_intersect_x <= mlx->data.map_width)
		&& (ray->vert_intersect_y >= (double)0 && ray->vert_intersect_y <= mlx->data.map_height))
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

	ray->x_intercept = floor(mlx->player.x / mlx->data.tile_size) * mlx->data.tile_size;
	if (ray_facing_right)
		ray->x_intercept += mlx->data.tile_size;

	ray->y_intercept = mlx->player.y + (ray->x_intercept - mlx->player.x) * tan(ray_angle);

	ray->x_step = mlx->data.tile_size;
	if (!ray_facing_right)
		ray->x_step = -ray->x_step;

	ray->y_step = mlx->data.tile_size * tan(ray_angle);
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

	ray_angle = mlx->player.angle - (mlx->data.fov / 2); // since fov == 60deg, you want half of your fov
	//to the right of the direction you are looking at (player.angle), and let's consider the angle of the
	//first ray: player.angle - half of fov
	i = 0;
	while (i < mlx->data.num_rays)
	{
		(mlx->data.rays + i)->angle = normalize_angle(ray_angle);
		cast_ray(mlx->data.rays + i, mlx);
		ray_angle += mlx->data.fov / mlx->data.num_rays; // after fiding the angle of the first ray (ray_angle)
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
	while (i < y + mlx->data.tile_size)
	{
		j = x;
		while (j < x + mlx->data.tile_size)
		{
			mlx_put_pixel(mlx->imgs.frame, j, i, color);
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

	map = mlx->data.map;
	i = 0;
	while (i < mlx->data.rows)
	{
		j = 0;
		while (j < mlx->data.columns)
		{
			if (map[i][j] - '0')
				color = 0xFF555194;
			else
				color = 0xFFFFFFFF;
			draw_map_tile(j * mlx->data.tile_size, i * mlx->data.tile_size, mlx, color);
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
				mlx_put_pixel(mlx->imgs.frame, mlx->player.x + x, mlx->player.y + y, mlx->player.color);
			x++;
		}
		y++;
	}
}

void	draw_ray(t_mlx *mlx, t_ray *ray, uint32_t ray_color)
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
		mlx_put_pixel(mlx->imgs.frame, x, y, ray_color);
		i++;
	}
}

void	draw_rays(t_mlx *mlx)
{
	uint32_t	ray_color;
	int			i;

	ray_color = 0x00FF00FF;
	i = 0;
	while (i < mlx->data.num_rays)
	{
		draw_ray(mlx, mlx->data.rays + i, ray_color);
		i++;
	}
}

uint8_t	*get_img_pixel_buffer(t_ray *ray, t_player *player, t_img *img)
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

	color_buffer = (uint32_t *)get_img_pixel_buffer(mlx->data.rays + x, &mlx->player, &mlx->imgs);
	textureX = (int)(mlx->data.rays + x)->wall_hit_x % (int)mlx->data.tile_size;
	if ((mlx->data.rays + x)->is_vertical_hit)
		textureX = (int)(mlx->data.rays + x)->wall_hit_y % (int)mlx->data.tile_size;
	i = y;
	if (i < 0)
		i = 0;
	while (i < (int)(y + wall_strip_height) && i < (int)mlx->data.screen_height)
	{
		textureY = (i - (int)y) * (mlx->data.tile_size / wall_strip_height);
		if (textureY > mlx->data.tile_size)
			break;
		color = color_buffer[(textureY * (int)mlx->data.tile_size) + textureX];
		mlx_put_pixel(mlx->imgs.frame, x, i++, color);
	}
}

void	draw_walls(t_mlx *mlx)
{
	int		i;
	double	wall_strip_height;
	double	distance_projection_plane;
	double	perp_distance;
	t_ray	*ray;

	distance_projection_plane = (mlx->data.screen_width / 2) / tan(mlx->data.fov / 2);
	i = 0;
	while (i < mlx->data.num_rays)
	{
		ray = mlx->data.rays + i;
		perp_distance = ray->distance * cos(ray->angle - mlx->player.angle);
		wall_strip_height = (mlx->data.tile_size / perp_distance) * distance_projection_plane;
		draw_wall(mlx, i, (mlx->data.screen_height / 2) - (wall_strip_height / 2), wall_strip_height);
		i++;
	}
}

void	draw_ceiling_and_floor(t_mlx *mlx)
{
	uint32_t	*color_buffer;
	uint32_t 	ceiling_color = mlx->data.C;
	uint32_t 	floor_color = mlx->data.F;
	uint32_t	i;
	uint32_t	j;

	color_buffer = (uint32_t *)mlx->imgs.frame->pixels;
	i = 0;
	//draw ceiling pixels
	while (i < mlx->imgs.frame->height / 2)
	{
		j = 0;
		while (j < mlx->imgs.frame->width)
			*(color_buffer + (i * mlx->imgs.frame->width) + j++) = ceiling_color; // (i * mlx.img.frame->width) is used to travel to the next row
		i++;
	}
	//draw floor pixels
	i = mlx->imgs.frame->height / 2;
	while (i < mlx->imgs.frame->height)
	{
		j = 0;
		while (j < mlx->imgs.frame->width)
			*(color_buffer + (i * mlx->imgs.frame->width) + j++) = floor_color;
		i++;
	}
}

void	draw_frame(t_mlx *mlx)
{
	draw_ceiling_and_floor(mlx);
	draw_walls(mlx);
	draw_map(mlx);
	draw_rays(mlx);
	draw_player(mlx);
	render_imgs(mlx, mlx->imgs.sprint_imgs, 14);
}

void	game_loop(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	update_player_on_keypress(mlx);
	cast_rays(mlx);
	draw_frame(mlx);
}

void	init_flg(t_flg *flg)
{
	flg->N_flg = 0;
	flg->S_flg = 0;
	flg->W_flg = 0;
	flg->E_flg = 0;
	flg->F_flg = 0;
	flg->C_flg = 0;
}
void f(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_map	map;

	if (ac != 2)
		return (write(2, "Wrong arguments\n", 16), 1);
	process_file_content(av[1], &map);
	init_cub3d(&mlx, &map);
	mlx_loop_hook(mlx.ptr, game_loop, &mlx);
	mlx_loop(mlx.ptr);
	free_game(&map);
	graceful_exit(&mlx);
	atexit(f);
}

// what is it to be done
	// animations are to be integrated
