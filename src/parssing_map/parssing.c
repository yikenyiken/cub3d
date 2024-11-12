/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:54:51 by messkely          #+#    #+#             */
/*   Updated: 2024/11/12 08:55:02 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	convert_rgb_to_hex(t_data *data, int color_buff[3], char c);
char	*add_spaces(char *col, int len);
void	normalize_map(t_data *data);
void	find_player_pos(t_data *data);
void	verify_texture_paths(t_data *data);

static	void	check_file_is_valid(char *file)
{
	while (*file)
	{
		if (*file == '.')
			if (check(file, ".cub") && *(file + 4) == '\0')
				return ;
		file++;
	}
	write(1, "ERROR: file is not valid\n", 25);
	exit(1);
}

static	char	*ft_read_file(char *map_path)
{
	int		fd;
	char	c;
	char	*map;
	int		count;

	fd = open(map_path, O_RDONLY);
	count = 0;
	if (fd < 0)
		exit(1);
	while (read(fd, &c, 1) == 1)
		count++;
	close(fd);
	if (count == 0)
		exit(1);
	map = (char *)malloc((count + 1) * sizeof(char));
	if (!map)
	{
		write(1, "Failed to allocate memory for map\n", 34);
		exit(1);
	}
	fd = open(map_path, O_RDONLY);
	read(fd, map, count);
	map[count] = '\0';
	return (close(fd), map);
}

void	check_elements(char *map)
{
	int		p_flg;
	int		i;

	p_flg = 0;
	i = 0;
	while (map[i])
	{
		if (map[i] != '0' && map[i] != '1' && map[i] != ' ' && map[i] != '\n')
		{
			if ((map[i] != 'N' && map[i] != 'S' && map[i] != 'E'
					&& map[i] != 'W') || p_flg)
				ft_error("check the element of map\n");
			else
				p_flg = 1;
		}
		i++;
	}
	if (map[i] == '\0' && !p_flg)
		ft_error("check the element of map\n");
}

void	process_file_content(char *map_path, t_data *data)
{
	char	*var_map;
	char	*map;
	t_flg	flg;

	check_file_is_valid(map_path);
	var_map = ft_read_file(map_path);
	map = check_file_elementes(data, var_map, &flg);
	check_elements(map);
	convert_rgb_to_hex(data, data->F, 'F');
	convert_rgb_to_hex(data, data->C, 'C');
	data->map = ft_split(data, map, '\n');
	check_walls(data, data->map);
	find_player_pos(data);
	normalize_map(data);
	verify_texture_paths(data);
	free(var_map);
}
