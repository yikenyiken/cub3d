/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:16:45 by messkely          #+#    #+#             */
/*   Updated: 2024/11/03 13:54:47 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	check_texture(t_map *my_map, char *file, char vector, int idx)
{
	int		i;
	char	*line;

	i = idx;
	line = NULL;
	while (file[i] && file[i] == ' ')
		i++;
	line = get_line(&file[i], '\n');
	if (!line)
		ft_error("Memory allocation failed\n");
	line = ft_trim(line);
	if (vector == 'N')
		my_map->NOpath = line;
	if (vector == 'S')
		my_map->SOpath = line;
	if (vector == 'W')
		my_map->WEpath = line;
	if (vector == 'E')
		my_map->EApath = line;
	increasing_flg(my_map->flg, vector);
	return (i++, i + ft_strlen(line));
}

static void	check_color_range(t_map *my_map, char *s, int i, char c)
{
	int	nb;

	if (!is_num(s) || ft_atoi(s) > 2147483647)
		ft_error("is not a number\n");
	nb = ft_atoi(s);
	if (nb >= 0 && nb <= 255)
	{
		if (c == 'F')
			my_map->F[i] = nb;
		else
			my_map->C[i] = nb;
	}
	else
		ft_error("check the color range errro\n");
}

static void	parse_color_val(t_map *my_map, char *line, char c)
{
	int		idx;
	char	**tmp;
	char	*nb;

	idx = 0;
	tmp = ft_split(my_map, line, ',');
	if (!tmp)
		ft_error("error of allocation\n");
	while (tmp[idx])
		idx++;
	if (idx != 3)
		ft_error("parse_color_val error\n");
	idx = 0;
	while (idx < 3)
	{
		nb = ft_trim(tmp[idx]);
		check_color_range(my_map, nb, idx, c);
		free(nb);
		idx++;
	}
	free(tmp);
}

int	check_colors(t_map *my_map, char *file, char c, int idx)
{
	char	*line;

	while (file[idx] && (file[idx] == ' ' || file[idx] == '\n'))
		idx++;
	line = get_line(file + idx, '\n');
	idx += ft_strlen(line);
	parse_color_val(my_map, line, c);
	free(line);
	increasing_flg(my_map->flg, c);
	return (idx);
}

char	*check_file_elementes(t_map *my_map, char *file, t_flg *flg)
{
	int	i;

	i = 0;
	my_map->flg = flg;
	init_flg(my_map->flg);
	while (file[i])
	{
		if (check(file + i, "NO"))
			i = check_texture(my_map, file, 'N', i + 2);
		if (check(file + i, "SO"))
			i = check_texture(my_map, file, 'S', i + 2);
		if (check(file + i, "WE"))
			i = check_texture(my_map, file, 'W', i + 2);
		if (check(file + i, "EA"))
			i = check_texture(my_map, file, 'E', i + 2);
		if (file[i] == 'F')
			i = check_colors(my_map, file, 'F', i + 1);
		if (file[i] == 'C')
			i = check_colors(my_map, file, 'C', i + 1);
		if (flg->break_flg || (file[i] != '\n' && file[i] != ' '))
			break ;
		while (file[i] && (file[i] == ' ' || file[i] == '\n'))
			i++;
	}
	return (check_flags(flg), file + i);
}
