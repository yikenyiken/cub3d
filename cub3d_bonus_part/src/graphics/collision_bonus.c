/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:14:19 by yiken             #+#    #+#             */
/*   Updated: 2025/01/02 11:54:54 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_wall_hit(t_mlx *mlx, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = x / mlx->data.tile_size;
	map_y = y / mlx->data.tile_size;
	return (mlx->data.map[map_y][map_x] - '0');
}

int	is_3d_collision(t_mlx *mlx, t_player *player)
{
	double	x_ahead_horz;
	double	y_ahead_horz;
	double	x_ahead_vert;
	double	y_ahead_vert;

	x_ahead_horz = player->x + cos(player->move_angle) * player->big_step;
	y_ahead_horz = player->y;
	x_ahead_vert = player->x;
	y_ahead_vert = player->y + sin(player->move_angle) * player->big_step;
	return (is_wall_hit(mlx, x_ahead_horz, y_ahead_horz)
		|| is_wall_hit(mlx, x_ahead_vert, y_ahead_vert)
		|| is_wall_hit(mlx, x_ahead_horz, y_ahead_vert));
}
