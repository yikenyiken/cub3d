/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:42:02 by yiken             #+#    #+#             */
/*   Updated: 2025/01/04 14:56:01 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	frame_put_pixel(t_mlx *mlx, int x, int y, uint32_t color);

void	draw_right_arm(t_mlx *mlx)
{
	int		i;
	int		x;
	int		y;
	double	waist_right_x;
	double	waist_right_y;

	i = 0;
	while (i < (int)mlx->player.radius)
	{
		waist_right_x = mlx->player.mini_x + cos(mlx->player.angle + (M_PI / 2))
			* mlx->player.radius;
		waist_right_y = mlx->player.mini_y + sin(mlx->player.angle + (M_PI / 2))
			* mlx->player.radius;
		x = waist_right_x + i * cos(mlx->player.angle);
		y = waist_right_y + i * sin(mlx->player.angle);
		frame_put_pixel(mlx, x, y, mlx->player.color);
		i++;
	}
}

void	draw_left_arm(t_mlx *mlx)
{
	int		i;
	int		x;
	int		y;
	double	waist_left_x;
	double	waist_left_y;

	i = 0;
	while (i < (int)mlx->player.radius)
	{
		waist_left_x = mlx->player.mini_x + cos(mlx->player.angle - (M_PI / 2))
			* mlx->player.radius;
		waist_left_y = mlx->player.mini_y + sin(mlx->player.angle - (M_PI / 2))
			* mlx->player.radius;
		x = waist_left_x + i * cos(mlx->player.angle);
		y = waist_left_y + i * sin(mlx->player.angle);
		frame_put_pixel(mlx, x, y, mlx->player.color);
		i++;
	}
}

void	draw_player_arms(t_mlx *mlx)
{
	draw_right_arm(mlx);
	draw_left_arm(mlx);
}

void	draw_player_head(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -(mlx->player.radius);
	while (y <= mlx->player.radius)
	{
		x = -(mlx->player.radius);
		while (x <= mlx->player.radius)
		{
			if (x * x + y * y <= mlx->player.radius * mlx->player.radius)
				frame_put_pixel(mlx, mlx->player.mini_x + x,
					mlx->player.mini_y + y, mlx->player.color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_mlx *mlx)
{
	draw_player_head(mlx);
	draw_player_arms(mlx);
}
