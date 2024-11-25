/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:59:10 by yiken             #+#    #+#             */
/*   Updated: 2024/11/25 16:16:27 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	delete_wall_txtrs(t_txtrs *txtrs)
{
	mlx_delete_texture(txtrs->wall_north);
	mlx_delete_texture(txtrs->wall_west);
	mlx_delete_texture(txtrs->wall_south);
	mlx_delete_texture(txtrs->wall_east);
}

void	load_wall_textures(t_mlx *mlx, t_txtrs *txtrs)
{
	txtrs->wall_north = mlx_load_png(mlx->data.wall_no_path);
	if (!txtrs->wall_north)
		graceful_exit(mlx, 1);
	txtrs->wall_west = mlx_load_png(mlx->data.wall_we_path);
	if (!txtrs->wall_west)
		(mlx_delete_texture(txtrs->wall_north), graceful_exit(mlx, 1));
	txtrs->wall_south = mlx_load_png(mlx->data.wall_so_path);
	if (!txtrs->wall_south)
		(mlx_delete_texture(txtrs->wall_north),
			mlx_delete_texture(txtrs->wall_west), graceful_exit(mlx, 1));
	txtrs->wall_east = mlx_load_png(mlx->data.wall_ea_path);
	if (!txtrs->wall_east)
	{
		mlx_delete_texture(txtrs->wall_north);
		mlx_delete_texture(txtrs->wall_west);
		(mlx_delete_texture(txtrs->wall_south), graceful_exit(mlx, 1));
	}
}

void	load_textures(t_mlx *mlx)
{
	load_wall_textures(mlx, &mlx->txtrs);
}
