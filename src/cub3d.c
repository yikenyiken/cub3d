/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:52:35 by yiken             #+#    #+#             */
/*   Updated: 2024/11/20 13:33:59 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	game_loop(void *param);
void	verify_arg_num(int ac);

int	main(int ac, char **av)
{
	t_mlx	mlx;

	verify_arg_num(ac);
	process_config_file(&mlx, av[1], &mlx.data);
	printf("C: %X, F: %X\n", mlx.data.ceiling_color, mlx.data.floor_color);
	init_cub3d(&mlx);
	mlx_loop_hook(mlx.ptr, game_loop, &mlx);
	mlx_loop(mlx.ptr);
	graceful_exit(&mlx, 0);
}
