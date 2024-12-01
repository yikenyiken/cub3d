/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:14:19 by yiken             #+#    #+#             */
/*   Updated: 2024/11/26 21:33:34 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_wall_hit(t_mlx *mlx, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = x / mlx->data.tile_size;
	map_y = y / mlx->data.tile_size;
	if (map_x < 0 || map_x >= mlx->data.columns
		|| map_y < 0 || map_y >= mlx->data.rows)
		return (1);
	return (mlx->data.map[map_y][map_x] - '0');
}
