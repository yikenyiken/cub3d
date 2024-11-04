/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:54:51 by messkely          #+#    #+#             */
/*   Updated: 2024/11/03 12:33:34 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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

void	process_file_content(char *map_path, t_map *my_map)
{
	char	*var_map;
	char	*map;
	t_flg	flg;

	check_file_is_valid(map_path);
	var_map = ft_read_file(map_path);
	map = check_file_elementes(my_map, var_map, &flg);
	convert_rgb_to_hex(my_map, my_map->F, 'F');
	convert_rgb_to_hex(my_map, my_map->C, 'C');
	my_map->map3D = ft_split(my_map, map, '\n');
	check_elements(map);
	check_walls(my_map, my_map->map3D);
	free(var_map);
}
