/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:15:48 by messkely          #+#    #+#             */
/*   Updated: 2024/12/01 12:48:54 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_0_or_dirs(char c);

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

static void	check_left_right_side(t_data *data, char **map, int rows)
{
	int	i;
	int	j;
	int	cols;

	i = 0;
	while (i < rows)
	{
		j = 0;
		cols = ft_strlen(map[i]);
		while (map[i][j])
		{
			if ((map[i][0] != '1' && map[i][0] != ' ')
				|| (map[i][cols - 1] != '1' && map[i][cols - 1] != ' '))
			{
				free_game(data);
				ft_error("map must be surrounded by walls\n");
			}
			j++;
		}
		i++;
	}
}

void	check_dirs_of_0(t_data *data, int i, int j, int cols)
{
	if (j == 0 || j == cols - 1 || i == 0 || i == data->rows - 1)
		(free_game(data), ft_error("poorly constructed map\n"));
	if (j < cols - 1 && !is_valid_char(data->map[i][j + 1]))
		(free_game(data), ft_error("poorly constructed map\n"));
	if (j > 0 && !is_valid_char(data->map[i][j - 1]))
		(free_game(data), ft_error("poorly constructed map\n"));
	if (i < data->rows - 1 && !is_valid_char(data->map[i + 1][j]))
		(free_game(data), ft_error("poorly constructed map\n"));
	if (i > 0 && !is_valid_char(data->map[i - 1][j]))
		(free_game(data), ft_error("poorly constructed map\n"));
}

void	check_0_is_dilemited(t_data *data)
{
	int	i;
	int	j;
	int	cols;

	i = 0;
	data->columns = 0;
	while (i < data->rows)
	{
		j = 0;
		cols = ft_strlen(data->map[i]);
		if (data->columns < cols)
			data->columns = cols;
		while (data->map[i][j])
		{
			if (is_0_or_dirs(data->map[i][j]))
				check_dirs_of_0(data, i, j, cols);
			j++;
		}
		i++;
	}
}

void	check_walls(t_data *data, char **map)
{
	int	cols;
	int	rows;
	int	i;

	rows = data->rows;
	cols = ft_strlen(map[0]);
	i = 0;
	while (i < cols)
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
			(free_game(data), ft_error("map must be surrounded by walls\n"));
		i++;
	}
	cols = ft_strlen(map[rows - 1]);
	i = 0;
	while (i < cols)
	{
		if (map[rows - 1][i] != '1' && map[rows - 1][i] != ' ')
			(free_game(data), ft_error("map must be surrounded by walls\n"));
		i++;
	}
	check_left_right_side(data, map, rows);
	check_0_is_dilemited(data);
}
