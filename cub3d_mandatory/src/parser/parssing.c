/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:54:51 by messkely          #+#    #+#             */
/*   Updated: 2024/11/25 18:42:57 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	convert_rgb_to_hex(t_data *data, int color_buff[3], char c);
char	*add_spaces(char *col, int len);
void	normalize_map(t_data *data);
void	find_player_pos(t_mlx *mlx);
void	verify_texture_paths(t_data *data);
void	check_blank_lines(char *map);

int	is_0_or_dirs(char c)
{
	return (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

void	check_file_is_valid(char *file)
{
	while (*file)
	{
		if (*file == '.')
			if (check(file, ".cub") && *(file + 4) == '\0')
				return ;
		file++;
	}
	ft_error("usage: ./cub3D [file name].cub\n");
}

char	*ft_read_file(char *map_path)
{
	int		fd;
	char	c;
	char	*map;
	int		count;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error("cannot read configuration file\n");
	count = 0;
	while (read(fd, &c, 1) == 1)
		count++;
	close(fd);
	if (count == 0)
		ft_error("configuration file is empty\n");
	map = (char *)malloc((count + 1) * sizeof(char));
	if (!map)
		ft_error("Memory allocation failure\n");
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		(free(map), ft_error("cannot read configuration file\n"));
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
				ft_error("outsider character(s) found in map\n");
			else
				p_flg = 1;
		}
		i++;
	}
	if (map[i] == '\0' && !p_flg)
		ft_error("player character missing (N E W S)\n");
	check_blank_lines(map);
}

// Detects any misconfiguration in the config file and gets the retievable data
void	process_config_file(t_mlx *mlx, char *map_path, t_data *data)
{
	char	*var_map;
	char	*map;
	t_flg	flg;

	check_file_is_valid(map_path);
	var_map = ft_read_file(map_path);
	map = check_file_elementes(data, var_map, &flg);
	free(var_map);
	check_elements(map);
	data->map = ft_split(data, map, '\n');
	check_walls(data, data->map);
	find_player_pos(mlx);
	normalize_map(data);
	verify_texture_paths(data);
}
