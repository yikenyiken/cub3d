/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:40:11 by yiken             #+#    #+#             */
/*   Updated: 2025/01/03 14:51:01 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

uint8_t	*get_wall_img_pxbuff(t_ray *ray, t_mlx *mlx);
void	frame_put_pixel(t_mlx *mlx, int x, int y, uint32_t color);

void	draw_wall_strip(t_mlx *mlx, int x, double y, double wall_strip_height)
{
	int			i;
	int			texture_x;
	int			texture_y;
	uint32_t	color;
	uint32_t	*wall_pxbuf;

	wall_pxbuf = (uint32_t *)get_wall_img_pxbuff(mlx->data.rays + x, mlx);
	texture_x = fmod((mlx->data.rays + x)->wall_hit_x, mlx->data.tile_size);
	if ((mlx->data.rays + x)->is_vertical_hit)
		texture_x = fmod((mlx->data.rays + x)->wall_hit_y, mlx->data.tile_size);
	i = y;
	if (i < 0)
		i = 0;
	while (i < (int)(y + wall_strip_height) && i < (int)mlx->data.screen_height)
	{
		texture_y = (i - (int)y) * (mlx->data.tile_size / wall_strip_height);
		if (texture_y > mlx->data.tile_size)
			break ;
		color = wall_pxbuf[(texture_y * (int)mlx->data.tile_size) + texture_x];
		frame_put_pixel(mlx, x, i++, color);
	}
}

void	draw_walls(t_mlx *mlx)
{
	int		i;
	double	wall_strip_height;
	double	distance_projection_plane;
	double	perp_distance;
	t_ray	*ray;

	distance_projection_plane = (mlx->data.screen_width / 2)
		/ tan(mlx->data.fov / 2);
	i = 0;
	while (i < mlx->data.num_rays)
	{
		ray = mlx->data.rays + i;
		perp_distance = ray->distance * cos(ray->angle - mlx->player.angle);
		wall_strip_height = (mlx->data.tile_size / perp_distance)
			* distance_projection_plane;
		draw_wall_strip(mlx, i, (mlx->data.screen_height / 2)
			- (wall_strip_height / 2), wall_strip_height);
		i++;
	}
}

void	draw_ceiling_and_floor(t_mlx *mlx)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < mlx->imgs.frame->height / 2)
	{
		j = 0;
		while (j < mlx->imgs.frame->width)
			frame_put_pixel(mlx, j++, i, mlx->data.ceiling_color);
		i++;
	}
	i = mlx->imgs.frame->height / 2;
	while (i < mlx->imgs.frame->height)
	{
		j = 0;
		while (j < mlx->imgs.frame->width)
			frame_put_pixel(mlx, j++, i, mlx->data.floor_color);
		i++;
	}
}

void	draw_3d_map(t_mlx *mlx)
{
	draw_ceiling_and_floor(mlx);
	draw_walls(mlx);
}
