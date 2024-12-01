/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_6_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:46:56 by messkely          #+#    #+#             */
/*   Updated: 2024/12/01 17:34:11 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

int	go_back(char *file, int i)
{
	if (i <= 0)
		return (0);
	while (i > 0 && file[i] != '\n')
		i--;
	if (file[i] == '\n')
		i++;
	return (i);
}

int	*create_rgb_buf(void)
{
	const int	colors_n = 3;
	int			*rgb_buf;

	rgb_buf = malloc(sizeof(int) * colors_n);
	if (!rgb_buf)
		return (NULL);
	return (rgb_buf);
}

void	check_map_dimensions(t_data *data)
{
	const int	max_cols = 100;
	const int	max_rows = 40;

	if (data->columns > max_cols || data->rows > max_rows)
	{
		free_game(data);
		ft_error("map dimensions limit exceeded\n");
	}
}

void	free_if_error(t_data *data, char **s, int idx, char *str)
{
	free_txtr_colors(data);
	while (idx < 3)
		free(s[idx++]);
	free(s);
	ft_error(str);
}
