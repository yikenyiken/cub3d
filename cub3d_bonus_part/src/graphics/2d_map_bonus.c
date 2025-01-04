/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:38:44 by yiken             #+#    #+#             */
/*   Updated: 2025/01/04 16:12:57 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	frame_put_pixel(t_mlx *mlx, int x, int y, uint32_t color);
void	draw_player(t_mlx *mlx);

int	is_border_pixel(int tile_size, int x, int y)
{
	if ((tile_size - 1) == (x % tile_size)
		|| (tile_size - 1) == (y % tile_size))
		return (1);
	return (0);
}

void	draw_map_tile(int x, int y, t_mlx *mlx, uint32_t color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + mlx->data.mini_tile_size)
	{
		j = x;
		while (j < x + mlx->data.mini_tile_size)
		{
			if (is_border_pixel(mlx->data.mini_tile_size, j, i))
				frame_put_pixel(mlx, j, i, mlx->data.tile_border_color);
			else
				frame_put_pixel(mlx, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_mlx *mlx)
{
	char		**map;
	int			i;
	int			j;

	map = mlx->data.map;
	i = 0;
	while (i < mlx->data.rows)
	{
		j = 0;
		while (j < mlx->data.columns)
		{
			if (map[i][j] == '1')
				draw_map_tile(j * mlx->data.mini_tile_size,
					i * mlx->data.mini_tile_size, mlx, mlx->data.floor_color);
			else if (map[i][j] == '0')
				draw_map_tile(j * mlx->data.mini_tile_size,
					i * mlx->data.mini_tile_size, mlx, mlx->data.map_color);
			j++;
		}
		i++;
	}
}

void	draw_2d_map(t_mlx *mlx)
{
	draw_map(mlx);
	draw_player(mlx);
}
