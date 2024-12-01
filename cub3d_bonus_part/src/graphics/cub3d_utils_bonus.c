/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:54:59 by yiken             #+#    #+#             */
/*   Updated: 2024/11/29 17:19:20 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	frame_put_pixel(t_mlx *mlx, int x, int y, uint32_t color)
{
	uint32_t	*frame_pixel_buffer;

	frame_pixel_buffer = (uint32_t *)mlx->imgs.frame->pixels;
	*(frame_pixel_buffer + (y * (int)mlx->imgs.frame->width) + x) = color;
}

uint32_t	*get_wall_img_pxbuff(t_ray *ray, t_mlx *mlx)
{
	t_player	*player;
	t_imgs		*imgs;
	uint8_t		*wall_img_pixel_buffer;

	player = &mlx->player;
	imgs = &mlx->imgs;
	wall_img_pixel_buffer = imgs->wall_north->pixels;
	if (ray->is_vertical_hit && ray->wall_hit_x > player->x)
		wall_img_pixel_buffer = imgs->wall_east->pixels;
	if (ray->is_vertical_hit && ray->wall_hit_x < player->x)
		wall_img_pixel_buffer = imgs->wall_west->pixels;
	if (!ray->is_vertical_hit && ray->wall_hit_y > player->y)
		wall_img_pixel_buffer = imgs->wall_south->pixels;
	return ((uint32_t *)wall_img_pixel_buffer);
}

void	verify_arg_num(int ac)
{
	if (ac != 2)
	{
		write(2, "Wrong argument number\n", 22);
		exit(1);
	}
}

// Renders the game and adjusts it by key events
void	game_loop(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	update_player_on_keypress(mlx);
	cast_rays(mlx);
	draw_3d_map(mlx);
	draw_2d_map(mlx);
}
