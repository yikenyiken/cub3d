/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:57:13 by yiken             #+#    #+#             */
/*   Updated: 2024/11/29 17:19:20 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	load_textures(t_mlx *mlx);
void	load_images(t_mlx *mlx);
void	free_parser_allocations(t_mlx *mlx);

void	create_window(t_mlx *mlx)
{
	mlx->ptr = mlx_init(mlx->data.screen_width, mlx->data.screen_height,
			"cub3D_bonus", 0);
	if (!mlx->ptr)
	{
		free_parser_allocations(mlx);
		free(mlx->data.rays);
		exit(1);
	}
}

void	render_frame_to_window(t_mlx *mlx)
{
	if (mlx_image_to_window(mlx->ptr, mlx->imgs.frame, 0, 0) == -1)
		graceful_exit(mlx, 1);
}

void	init_mlx(t_mlx *mlx)
{
	create_window(mlx);
	load_textures(mlx);
	load_images(mlx);
	render_frame_to_window(mlx);
}
