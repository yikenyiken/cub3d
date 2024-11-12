/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:53:26 by messkely          #+#    #+#             */
/*   Updated: 2024/11/12 08:54:41 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	check_player_angle(t_data *data, char dir)
{
	if (dir == 'N')
		data->player_angle = (3 * M_PI) / 2;
	else if (dir == 'S')
		data->player_angle = M_PI / 2;
	else if (dir == 'E')
		data->player_angle = 0.0;
	else if (dir == 'W')
		data->player_angle = M_PI;
}

void	find_player_pos(t_data *data)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = data->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				data->player_pos[0] = j;
				data->player_pos[1] = i;
				check_player_angle(data, map[i][j]);
				data->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
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
