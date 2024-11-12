/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:46:36 by messkely          #+#    #+#             */
/*   Updated: 2024/11/12 08:54:03 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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

char	*add_spaces(char *col, int len)
{
	int		i;
	int		j;
	char	*buff;

	buff = malloc((len + 1) * sizeof(char));
	if (!buff)
		return (NULL);
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
		data->map[i] = add_spaces(data->map[i], data->columns);
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
		printf("Error: path is invalid\n");
		perror(path);
		free_game(data);
		exit(1);
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
