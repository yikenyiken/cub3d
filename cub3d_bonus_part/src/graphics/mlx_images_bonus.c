/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:03:33 by yiken             #+#    #+#             */
/*   Updated: 2024/11/29 17:19:20 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	delete_wall_txtrs(t_txtrs *txtrs);

void	wall_txtrs_to_imgs(t_mlx *mlx, t_txtrs *txtrs, t_imgs *imgs)
{
	imgs->frame = mlx_new_image(mlx->ptr, mlx->data.screen_width,
			mlx->data.screen_height);
	imgs->wall_north = mlx_texture_to_image(mlx->ptr, txtrs->wall_north);
	imgs->wall_west = mlx_texture_to_image(mlx->ptr, txtrs->wall_west);
	imgs->wall_south = mlx_texture_to_image(mlx->ptr, txtrs->wall_south);
	imgs->wall_east = mlx_texture_to_image(mlx->ptr, txtrs->wall_east);
}

void	handle_txtr_to_img_fail(t_mlx *mlx, t_imgs *imgs)
{
	if (!imgs->wall_north || !imgs->wall_west
		|| !imgs->wall_south || !imgs->wall_east
		|| !imgs->frame)
		graceful_exit(mlx, 1);
}

void	resize_imgs(t_mlx *mlx, t_imgs *imgs, int nwidth, int nheight)
{
	if (!mlx_resize_image(imgs->wall_north, nwidth, nheight)
		|| !mlx_resize_image(imgs->wall_west, nwidth, nheight)
		|| !mlx_resize_image(imgs->wall_south, nwidth, nheight)
		|| !mlx_resize_image(imgs->wall_east, nwidth, nheight))
		graceful_exit(mlx, 1);
}

void	load_images(t_mlx *mlx)
{
	int		tile_size;

	tile_size = mlx->data.tile_size;
	wall_txtrs_to_imgs(mlx, &mlx->txtrs, &mlx->imgs);
	delete_wall_txtrs(&mlx->txtrs);
	handle_txtr_to_img_fail(mlx, &mlx->imgs);
	resize_imgs(mlx, &mlx->imgs, tile_size, tile_size);
}
