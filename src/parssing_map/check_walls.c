/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:15:48 by messkely          #+#    #+#             */
/*   Updated: 2024/10/23 18:16:50 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

void	check_left_right_side(char **map3D, int rows)
{
	int	i;
	int	j;
	int	cols;

	i = 0;
	while (i < rows)
	{
		j = 0;
		cols = ft_strlen(map3D[i]);
		while (map3D[i][j])
		{
			if ((map3D[i][0] != '1' && map3D[i][0] != ' ')
				|| (map3D[i][cols - 1] != '1' && map3D[i][cols - 1] != ' '))
				ft_error("check the left and the right side\n");
			j++;
		}
		i++;
	}
}

void	check_0_is_dilemited(char **map3D, int rows)
{
	int	i;
	int	j;
	int	cols;

	i = 0;
	while (i < rows)
	{
		j = 0;
		cols = ft_strlen(map3D[i]);
		while (map3D[i][j])
		{
			if (map3D[i][j] == '0')
			{
				if (j == 0 || j == cols - 1 || i == 0 || i == rows - 1)
					ft_error("0 at the edge is not delimited\n");
				if (j < cols - 1 && !is_valid_char(map3D[i][j + 1]))
					ft_error("check 0 is dilemited\n");
				if (j > 0 && !is_valid_char(map3D[i][j - 1]))
					ft_error("check 0 is dilemited\n");
				if (i < rows - 1 && !is_valid_char(map3D[i + 1][j]))
					ft_error("check 0 is dilemited\n");
				if (i > 0 && !is_valid_char(map3D[i - 1][j]))
					ft_error("check 0 is dilemited\n");
			}
			j++;
		}
		i++;
	}
}


void	check_walls(t_map *map, char **map3D)
{
	int	cols;
	int	rows;
	int	i;

	rows = map->rows_size;
	// check the first row
	cols = ft_strlen(map3D[0]);
	i = 0;
	while (i < cols)
	{
		if (map3D[0][i] != '1' && map3D[0][i] != ' ')
			ft_error("check the first row\n");
		i++;
	}
	// check the last row
	cols = ft_strlen(map3D[rows - 1]);
	i = 0;
	while (i < cols)
	{
		if (map3D[rows - 1][i] != '1' && map3D[rows - 1][i] != ' ')
			ft_error("check the last row\n");
		i++;
	}
	// check the left and the right side
	check_left_right_side(map3D, rows);
	// check 0 is dilemited by 1 ou 0 ou the vectors
	check_0_is_dilemited(map3D, rows);
}
