/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_4_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:46:36 by messkely          #+#    #+#             */
/*   Updated: 2025/01/04 11:29:21 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

int	check(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (to_find[i])
	{
		if (to_find[i] != str[i])
			return (0);
		i++;
	}
	if (to_find[i] == '\0')
		return (1);
	return (0);
}

char	*add_spaces(t_data *data, char *col, int len)
{
	int		i;
	int		j;
	char	*buff;

	buff = malloc((len + 1) * sizeof(char));
	if (!buff)
	{
		free_game(data);
		ft_error("Memory allocation failure\n");
	}
	i = 0;
	j = 0;
	while (i < len)
	{
		if (col[j])
			buff[i] = col[j++];
		else
			buff[i] = ' ';
		i++;
	}
	buff[i] = '\0';
	return (free(col), buff);
}

void	normalize_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		data->map[i] = add_spaces(data, data->map[i], data->columns);
		i++;
	}
	data->map[i] = NULL;
}

void	single_path_verify(t_data *data, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free_game(data);
		ft_error("verify texture elements' information\n");
	}
	close(fd);
}

void	verify_texture_paths(t_data *data)
{
	single_path_verify(data, data->wall_no_path);
	single_path_verify(data, data->wall_we_path);
	single_path_verify(data, data->wall_so_path);
	single_path_verify(data, data->wall_ea_path);
}
