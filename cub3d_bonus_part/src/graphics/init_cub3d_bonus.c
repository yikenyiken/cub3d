/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:19:39 by yiken             #+#    #+#             */
/*   Updated: 2024/12/01 13:26:43 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	init_mlx(t_mlx *mlx);
void	set_player_xy(t_player *player, double x, double y);
void	set_player_mini_xy(t_player *player, double x, double y);
t_ray	*create_rays(t_mlx *mlx, t_data *data);

void	init_data(t_mlx *mlx, t_data *data)
{
	data->fov = 60 * (M_PI / 180);
	data->screen_width = 1600;
	data->screen_height = 1200;
	data->tile_size = 50;
	data->mini_tile_size = 10;
	data->map_width = data->tile_size * data->columns;
	data->map_height = data->tile_size * data->rows;
	data->num_rays = data->screen_width;
	data->map_color = 0xFFFFFFFF;
	data->tile_border_color = 0xFF000000;
	data->rays = create_rays(mlx, data);
}

void	init_player(t_player *player, t_data *data)
{
	double	player_x;
	double	player_y;
	double	player_mini_x;
	double	player_mini_y;

	player_x = player->x * data->tile_size + (data->tile_size / 2);
	player_y = player->y * data->tile_size + (data->tile_size / 2);
	player_mini_x = player->x * data->mini_tile_size
		+ (data->mini_tile_size / 2);
	player_mini_y = player->y * data->mini_tile_size
		+ (data->mini_tile_size / 2);
	set_player_xy(player, player_x, player_y);
	set_player_mini_xy(player, player_mini_x, player_mini_y);
	player->radius = 3;
	player->move_step = 3;
	player->mini_move_step = player->move_step
		* (data->mini_tile_size / data->tile_size);
	player->rotation_step = 1.55 * (M_PI / 180);
	player->color = 0xAAAAAAAA;
	player->is_moving = 0;
	player->big_step = 10;
}

// Initalizes the remaining data
// and prepares the necessary resources for the game
void	init_cub3d(t_mlx *mlx)
{
	init_data(mlx, &mlx->data);
	init_player(&mlx->player, &mlx->data);
	init_mlx(mlx);
}
