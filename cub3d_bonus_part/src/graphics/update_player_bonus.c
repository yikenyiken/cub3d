/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:50:58 by yiken             #+#    #+#             */
/*   Updated: 2025/01/02 11:54:54 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	vert_move_listen(t_mlx *mlx, t_player *player);
void	horz_move_listen(t_mlx *mlx, t_player *player);
void	up_diagonal_move_listen(t_mlx *mlx, t_player *player);
void	down_diagonal_move_listen(t_mlx *mlx, t_player *player);
void	game_exit_listen(t_mlx *mlx);
int		is_wall_hit(t_mlx *mlx, double x, double y);
void	set_player_mini_xy(t_player *player, double x, double y);
int		is_3d_collision(t_mlx *mlx, t_player *player);

void	set_move_attributes(t_player *player, double move_angle)
{
	player->is_moving = 1;
	player->move_angle = move_angle;
}

void	set_player_xy(t_player *player, double x, double y)
{
	player->x = x;
	player->y = y;
}

void	set_player_mini_xy(t_player *player, double x, double y)
{
	player->mini_x = x;
	player->mini_y = y;
}

void	update_player_by_events(t_mlx *mlx, t_player *player)
{
	double	new_x;
	double	new_y;
	double	new_mini_x;
	double	new_mini_y;

	if (!player->is_moving)
		return ;
	player->is_moving = 0;
	new_x = player->x + cos(player->move_angle) * player->move_step;
	new_y = player->y + sin(player->move_angle) * player->move_step;
	new_mini_x = player->mini_x + cos(player->move_angle)
		* player->mini_move_step;
	new_mini_y = player->mini_y + sin(player->move_angle)
		* player->mini_move_step;
	if (!is_3d_collision(mlx, player))
	{
		set_player_xy(&mlx->player, new_x, new_y);
		set_player_mini_xy(&mlx->player, new_mini_x, new_mini_y);
	}
}

void	update_player_on_keypress(t_mlx *mlx)
{
	vert_move_listen(mlx, &mlx->player);
	horz_move_listen(mlx, &mlx->player);
	up_diagonal_move_listen(mlx, &mlx->player);
	down_diagonal_move_listen(mlx, &mlx->player);
	update_player_by_events(mlx, &mlx->player);
	game_exit_listen(mlx);
}
