/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:38:44 by yiken             #+#    #+#             */
/*   Updated: 2024/11/17 18:09:13 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_player_head(t_mlx *mlx);
void	frame_put_pixel(t_mlx *mlx, int x, int y, uint32_t color);
void	draw_player(t_mlx *mlx);

int	is_wall_hit(t_mlx *mlx, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = x / mlx->data.tile_size;
	map_y = y / mlx->data.tile_size;
	return (mlx->data.map[map_y][map_x] - '0');
}

void	draw_map_tile(int x, int y, t_mlx *mlx, uint32_t color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + mlx->data.tile_size)
	{
		j = x;
		while (j < x + mlx->data.tile_size)
		{
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
				draw_map_tile(j * mlx->data.tile_size,
					i * mlx->data.tile_size, mlx, mlx->data.floor_color);
			else if (map[i][j] == '0')
				draw_map_tile(j * mlx->data.tile_size,
					i * mlx->data.tile_size, mlx, 0xFFFFFFFF); // is this color to reside in a variable
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
