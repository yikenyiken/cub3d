/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:15:48 by messkely          #+#    #+#             */
/*   Updated: 2024/11/11 16:26:40 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

static void	check_left_right_side(char **map, int rows)
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
				ft_error("check the left and the right side\n");
			j++;
		}
		i++;
	}
}

void	check_dirs_of_0(t_data *data, int i, int j, int cols)
{
	if (j == 0 || j == cols - 1 || i == 0 || i == data->rows - 1)
		ft_error("0 at the edge is not delimited\n");
	if (j < cols - 1 && !is_valid_char(data->map[i][j + 1]))
		ft_error("check 0 is dilemited\n");
	if (j > 0 && !is_valid_char(data->map[i][j - 1]))
		ft_error("check 0 is dilemited\n");
	if (i < data->rows - 1 && !is_valid_char(data->map[i + 1][j]))
		ft_error("check 0 is dilemited\n");
	if (i > 0 && !is_valid_char(data->map[i - 1][j]))
		ft_error("check 0 is dilemited\n");
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
			if (data->map[i][j] == '0')
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
			ft_error("check the first row\n");
		i++;
	}
	cols = ft_strlen(map[rows - 1]);
	i = 0;
	while (i < cols)
	{
		if (map[rows - 1][i] != '1' && map[rows - 1][i] != ' ')
			ft_error("check the last row\n");
		i++;
	}
	check_left_right_side(map, rows);
	check_0_is_dilemited(data);
}
