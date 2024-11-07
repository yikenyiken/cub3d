/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:54:51 by messkely          #+#    #+#             */
/*   Updated: 2024/11/05 14:59:26 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static	void	check_file_is_valid(char *file)
{
	while (*file)
	{
		if (*file == '.')
			if (check(file, ".cub"))
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
	// while (read(fd, &c, 1) == 1 && count <= MAX_WIDTH * MAX_HEIGHT)
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

void	check_player_angle(t_map *map, char dir)
{
	if (dir == 'N')
		map->player_angle = (3 * M_PI) / 2;
	else if (dir == 'S')
		map->player_angle = M_PI / 2;
	else if (dir == 'E')
		map->player_angle = 0.0;
	else if (dir == 'W')
		map->player_angle = M_PI;
}

void	find_player_pos(t_map *map)
{
	int		i;
	int		j;
	char	**map2d;

	i = 0;
	map2d = map->map3D;
	while (map2d[i])
	{
		j = 0;
		while (map2d[i][j])
		{
			if (map2d[i][j] == 'N' || map2d[i][j] == 'S'
				|| map2d[i][j] == 'W' || map2d[i][j] == 'E')
			{
				map->player_pos[0] = j;
				map->player_pos[1] = i;
				check_player_angle(map, map2d[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	process_file_content(char *map_path, t_map *my_map)
{
	char	*var_map;
	char	*map;
	t_flg	flg;

	check_file_is_valid(map_path);
	var_map = ft_read_file(map_path);
	map = check_file_elementes(my_map, var_map, &flg);
	check_elements(map);
	convert_rgb_to_hex(my_map, my_map->F, 'F');
	convert_rgb_to_hex(my_map, my_map->C, 'C');
	my_map->map3D = ft_split(my_map, map, '\n');
	check_walls(my_map, my_map->map3D);
	find_player_pos(my_map);
	free(var_map);
}
