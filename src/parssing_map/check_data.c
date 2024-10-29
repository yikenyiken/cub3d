/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_elementes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:03:07 by messkely          #+#    #+#             */
/*   Updated: 2024/10/23 15:05:18 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static char	*get_line(char *s, char c)
{
	char	*arr;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	arr = malloc((i + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
		(arr[i] = s[i], i++);
	return (arr[i] = '\0', arr);
}

static int	check_texture(t_map *my_map, char *file, char *vector, int idx)
{
	int 	i;
	char	*line = NULL;

	i = idx;
	if (check(file + i, vector))
	{
		i += 2;
		while (file[i] && (file[i] == ' '))
			i++;
		if (file[i])
		{
			line = get_line(&file[i], '\n');
			if (!line)
				return (ft_error("Memory allocation failed for texture path\n"), i);
			if (vector[0] == 'N')
				my_map->NOpath = line;
			if (vector[0] == 'S')
				my_map->SOpath = line;
			if (vector[0] == 'W')
				my_map->WEpath = line;
			if (vector[0] == 'E')
				my_map->EApath = line;
		}
	}
	i++;
	return (i + ft_strlen(line));
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
	// check the range
	idx = 0;
	while (idx < 3)
	{
		nb =  ft_trim(tmp[idx]);
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
	// parse the range of colors
	parse_color_val(my_map, line, c);
	free(line);
	return (idx);
}

char	*check_file_elementes(t_map *my_map, char *file)
{
	int	i;
	t_flg flg;

	(i = 0, init_flg(&flg));
	while (file[i])
	{
		if (file[i] == 'N')
			(i = check_texture(my_map, file, "NO", i), flg.N_flg++);
		if (file[i] == 'S')
			(i = check_texture(my_map, file, "SO", i), flg.S_flg++);
		if (file[i] == 'W')
			(i = check_texture(my_map, file, "WE", i), flg.W_flg++);
		if (file[i] == 'E')
			(i = check_texture(my_map, file, "EA", i), flg.E_flg++);
		if (file[i] == 'F')
			(i = check_colors(my_map, file, 'F', i + 1), flg.F_flg++);
		if (file[i] == 'C')
			(i = check_colors(my_map, file, 'C', i + 1), flg.C_flg++);
		if (flg.N_flg && flg.S_flg && flg.W_flg && flg.E_flg
			&& flg.F_flg && flg.C_flg)
			break;
		while (file[i] && (file[i] == ' ' || file[i] == '\n'))
			i++;
	}
	if (flg.N_flg != 1 || flg.S_flg != 1 || flg.W_flg != 1
			|| flg.E_flg != 1 || flg.F_flg != 1
			|| flg.C_flg != 1) ft_error("check data\n");
	return (file + i);
}

void	convert_RGB_to_hex(t_map *map, int color_buff[3], char c)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = color_buff[0];
	g = color_buff[1];
	b = color_buff[2];
	a = 255;
	if (c == 'F')
		map->Fhex = (a << 24) | (r << 16) | (g << 8) | b;
	else
		map->Chex = (a << 24) | (r << 16) | (g << 8) | b;
}
