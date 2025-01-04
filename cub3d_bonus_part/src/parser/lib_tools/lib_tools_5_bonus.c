/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_5_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:53:26 by messkely          #+#    #+#             */
/*   Updated: 2025/01/04 12:05:36 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	check_player_angle(t_player *player, char dir)
{
	if (dir == 'N')
		player->angle = (3 * M_PI) / 2;
	else if (dir == 'S')
		player->angle = M_PI / 2;
	else if (dir == 'E')
		player->angle = 0.0;
	else if (dir == 'W')
		player->angle = M_PI;
}

void	find_player_pos(t_mlx *mlx)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = mlx->data.map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				mlx->player.x = j;
				mlx->player.y = i;
				check_player_angle(&mlx->player, map[i][j]);
				map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int	is_blank_line(char *map)
{
	while (*map == ' ')
		map++;
	return (*map == '\n' || *map == '\0');
}

void	check_blank_lines(t_data *data, char *map, int blank_line)
{
	int		found_content;
	char	*tmp;

	found_content = 0;
	tmp = map;
	while (*map && (*map != '\n' || *map == ' '))
		map++;
	while (*map)
	{
		if (is_blank_line(map))
		{
			if (found_content)
				blank_line = 1;
		}
		else
		{
			found_content = 1;
			if (blank_line)
				(free(tmp), free_txtr_paths(data),
					ft_error("empty line in map\n"));
		}
		while (*map && *map != '\n')
			map++;
		*map == '\n' && map++;
	}
}

void	free_game(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
		free(data->map[i++]);
	free(data->map);
	free(data->wall_ea_path);
	free(data->wall_no_path);
	free(data->wall_so_path);
	free(data->wall_we_path);
}
