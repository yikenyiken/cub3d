/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:52:35 by yiken             #+#    #+#             */
/*   Updated: 2024/11/12 11:30:02 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	graceful_exit(t_mlx *mlx, int code)
{
	free(mlx->data->rays);
	mlx_terminate(mlx->ptr); // this function include all previously created images in the cleanup process
	exit(code);
}

void	game_loop(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	update_player_on_keypress(mlx);
	cast_rays(mlx);
	draw_3d_map(mlx);
	draw_2d_map(mlx);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_data	data;

	if (ac != 2)
		return (write(2, "Wrong arguments\n", 16), 1);
	process_file_content(av[1], &data);
	init_cub3d(&mlx, &data);
	mlx_loop_hook(mlx.ptr, game_loop, &mlx);
	mlx_loop(mlx.ptr);
	free_game(&data);
	graceful_exit(&mlx, 0);
}
