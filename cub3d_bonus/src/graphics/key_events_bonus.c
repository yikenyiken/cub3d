/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:59:51 by yiken             #+#    #+#             */
/*   Updated: 2024/11/25 16:16:28 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	virtual_player_move(t_player *player, double new_angle);

void	game_exit_listen(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_ESCAPE))
		graceful_exit(mlx, 0);
}

void	vert_move_listen(t_mlx *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_W)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_A)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_D)))
	{
		virtual_player_move(player, player->angle);
	}
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_S)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_A)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_D)))
	{
		virtual_player_move(player, player->angle + M_PI);
	}
}

void	horz_move_listen(t_mlx *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_D)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_W)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_S)))
	{
		virtual_player_move(player, player->angle + M_PI / 2);
	}
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_A)
		&& (!mlx_is_key_down(mlx->ptr, MLX_KEY_W)
			&& !mlx_is_key_down(mlx->ptr, MLX_KEY_S)))
	{
		virtual_player_move(player, player->angle - M_PI / 2);
	}
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_RIGHT))
		mlx->player.angle += mlx->player.rotation_step;
	else if (mlx_is_key_down(mlx->ptr, MLX_KEY_LEFT))
		mlx->player.angle -= mlx->player.rotation_step;
}

void	up_diagonal_move_listen(t_mlx *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_W)
		&& mlx_is_key_down(mlx->ptr, MLX_KEY_D))
	{
		virtual_player_move(player, player->angle + (M_PI / 2) / 2);
	}
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_W)
		&& mlx_is_key_down(mlx->ptr, MLX_KEY_A))
	{
		virtual_player_move(player, player->angle - (M_PI / 2) / 2);
	}
}

void	down_diagonal_move_listen(t_mlx *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_S)
		&& mlx_is_key_down(mlx->ptr, MLX_KEY_D))
	{
		virtual_player_move(player, player->angle + M_PI - (M_PI / 2 / 2));
	}
	if (mlx_is_key_down(mlx->ptr, MLX_KEY_S)
		&& mlx_is_key_down(mlx->ptr, MLX_KEY_A))
	{
		virtual_player_move(player, player->angle + M_PI + (M_PI / 2 / 2));
	}
}
