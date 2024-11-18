/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:50:58 by yiken             #+#    #+#             */
/*   Updated: 2024/11/17 19:03:59 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	vert_move_listen(t_mlx *mlx, t_player *player);
void	horz_move_listen(t_mlx *mlx, t_player *player);
void	up_diagonal_move_listen(t_mlx *mlx, t_player *player);
void	down_diagonal_move_listen(t_mlx *mlx, t_player *player);
void	game_exit_listen(t_mlx *mlx);
int		is_wall_hit(t_mlx *mlx, double x, double y);

void	set_player_xy(t_player *player, double x, double y)
{
	player->x = x;
	player->y = y;
}

int	is_3d_collision(t_mlx *mlx, t_player *player)
{
	double	x_ahead_horz;
	double	y_ahead_horz;
	double	x_ahead_vert;
	double	y_ahead_vert;

	x_ahead_horz = player->x + cos(player->new_angle) * player->big_step;
	y_ahead_horz = player->y;
	x_ahead_vert = player->x;
	y_ahead_vert = player->y + sin(player->new_angle) * player->big_step;
	return (is_wall_hit(mlx, x_ahead_horz, y_ahead_horz)
		|| is_wall_hit(mlx, x_ahead_vert, y_ahead_vert)
		|| is_wall_hit(mlx, x_ahead_horz, y_ahead_vert));
}

void	update_player_by_events(t_mlx *mlx, t_player *player)
{
	double	new_x;
	double	new_y;

	if (!player->is_moving)
		return ;
	player->is_moving = 0;
	new_x = player->x + cos(player->new_angle) * player->move_step;
	new_y = player->y + sin(player->new_angle) * player->move_step;
	if (!is_3d_collision(mlx, player))
		set_player_xy(&mlx->player, new_x, new_y);
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
