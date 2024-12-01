/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:19:39 by yiken             #+#    #+#             */
/*   Updated: 2024/12/01 13:12:01 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_mlx(t_mlx *mlx);
void	set_player_xy(t_player *player, double x, double y);
t_ray	*create_rays(t_mlx *mlx, t_data *data);

void	init_data(t_mlx *mlx, t_data *data)
{
	data->fov = 60 * (M_PI / 180);
	data->screen_width = 1600;
	data->screen_height = 1200;
	data->tile_size = 50;
	data->map_width = data->tile_size * data->columns;
	data->map_height = data->tile_size * data->rows;
	data->num_rays = data->screen_width;
	data->rays = create_rays(mlx, data);
}

void	init_player(t_player *player, t_data *data)
{
	double	player_x;
	double	player_y;

	player_x = player->x * data->tile_size + (data->tile_size / 2);
	player_y = player->y * data->tile_size + (data->tile_size / 2);
	set_player_xy(player, player_x, player_y);
	player->move_step = 3;
	player->rotation_step = 1.55 * (M_PI / 180);
	player->is_moving = 0;
}

// Initalizes the remaining data
// and prepares the necessary resources for the game
void	init_cub3d(t_mlx *mlx)
{
	init_data(mlx, &mlx->data);
	init_player(&mlx->player, &mlx->data);
	init_mlx(mlx);
}
