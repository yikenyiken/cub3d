/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:16:45 by messkely          #+#    #+#             */
/*   Updated: 2024/11/25 16:19:11 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	convert_rgb_to_hex(t_data *data, int color_buff[3], char c);

static int	check_texture(t_data *data, char *file, char vector, int idx)
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
		data->wall_no_path = line;
	if (vector == 'S')
		data->wall_so_path = line;
	if (vector == 'W')
		data->wall_we_path = line;
	if (vector == 'E')
		data->wall_ea_path = line;
	increasing_flg(data->flg, vector);
	return (i++, i + ft_strlen(line));
}

static void	check_color_range(t_data *data, char *s, int i, char c)
{
	int	nb;

	if (!is_num(s))
		ft_error("found outsider character(s) in color(s)\n");
	if (ft_atoi(s) > 2147483647)
		ft_error("color value(s) out of range\n");
	nb = ft_atoi(s);
	if (nb >= 0 && nb <= 255)
	{
		if (c == 'F')
			data->floor_rgb_buf[i] = nb;
		else if (c == 'C')
			data->ceiling_rgb_buf[i] = nb;
	}
	else
		ft_error("color value(s) out of range\n");
}

static void	parse_color_val(t_data *data, char *line, char c)
{
	int		idx;
	char	**tmp;
	char	*nb;

	idx = 0;
	tmp = ft_split(data, line, ',');
	if (!tmp)
		ft_error("error of allocation\n");
	while (tmp[idx])
		idx++;
	if (idx != 3)
		ft_error("Color format syntax error.\n");
	idx = 0;
	while (idx < 3)
	{
		nb = ft_trim(tmp[idx]);
		check_color_range(data, nb, idx, c);
		free(nb);
		idx++;
	}
	free(tmp);
}

int	check_colors(t_data *data, char *file, char c, int idx)
{
	char	*line;

	data->floor_rgb_buf = create_rgb_buf();
	data->ceiling_rgb_buf = create_rgb_buf();
	while (file[idx] && (file[idx] == ' ' || file[idx] == '\n'))
		idx++;
	line = get_line(file + idx, '\n');
	idx += ft_strlen(line);
	parse_color_val(data, line, c);
	free(line);
	increasing_flg(data->flg, c);
	if (c == 'F')
		convert_rgb_to_hex(data, data->floor_rgb_buf, 'F');
	else if (c == 'C')
		convert_rgb_to_hex(data, data->ceiling_rgb_buf, 'C');
	if (c == 'F')
		convert_rgb_to_hex(data, data->floor_rgb_buf, 'F');
	else if (c == 'C')
		convert_rgb_to_hex(data, data->ceiling_rgb_buf, 'C');
	free(data->floor_rgb_buf);
	free(data->ceiling_rgb_buf);
	return (idx);
}

char	*check_file_elementes(t_data *data, char *file, t_flg *flg)
{
	int	i;

	i = 0;
	data->flg = flg;
	init_flg(data->flg);
	while (file[i])
	{
		if (check(file + i, "NO"))
			i = check_texture(data, file, 'N', i + 2);
		else if (check(file + i, "SO"))
			i = check_texture(data, file, 'S', i + 2);
		else if (check(file + i, "WE"))
			i = check_texture(data, file, 'W', i + 2);
		else if (check(file + i, "EA"))
			i = check_texture(data, file, 'E', i + 2);
		else if (file[i] == 'F')
			i = check_colors(data, file, 'F', i + 1);
		else if (file[i] == 'C')
			i = check_colors(data, file, 'C', i + 1);
		else if (flg->break_flg || (file[i] != ' ' && file[i] != '\n'))
			break ;
		while (file[i] && (file[i] == ' ' || file[i] == '\n'))
			i++;
	}
	if (file[i] == '1')
		i = go_back(file, i);
	return (check_flags(flg), file + i);
}
