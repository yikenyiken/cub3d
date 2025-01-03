/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:16:45 by messkely          #+#    #+#             */
/*   Updated: 2025/01/03 17:51:30 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	convert_rgb_to_hex(t_data *data, int color_buff[3], char c);
char	*ft_strdup(char *s);
char	**ft_split_colors(t_data *data, char *s, char c);

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
		(free(file), free_txtr_paths(data), ft_error("allocation failed\n"));
	line = ft_trim(line);
	if (vector == 'N' && data->flg->n_flg == 0)
		data->wall_no_path = line;
	else if (vector == 'S' && data->flg->s_flg == 0)
		data->wall_so_path = line;
	else if (vector == 'W' && data->flg->w_flg == 0)
		data->wall_we_path = line;
	else if (vector == 'E' && data->flg->e_flg == 0)
		data->wall_ea_path = line;
	else
	{
		free_txtr_paths(data);
		(free(file), free(line), ft_error("duplicated element found\n"));
	}
	return (increasing_flg(data->flg, vector), i + ft_strlen(line) + 1);
}

static void	check_color_range(t_data *data, char **s, int i, char c)
{
	int	nb;

	if (!is_num(s[i]))
		free_if_error(data, s, i, "found outsider character in color(s)\n");
	if (ft_atoi(s[i]) > 2147483647)
		free_if_error(data, s, i, "color value(s) out of range\n");
	nb = ft_atoi(s[i]);
	if (nb >= 0 && nb <= 255)
	{
		if (c == 'F')
			data->floor_rgb_buf[i] = nb;
		else if (c == 'C')
			data->ceiling_rgb_buf[i] = nb;
	}
	else
		free_if_error(data, s, i, "color value(s) out of range\n");
}

static void	parse_color_val(t_data *data, char *line, char c, char *file)
{
	int		idx;
	char	**tmp;

	idx = 0;
	tmp = ft_split_colors(data, line, ',');
	if (!tmp)
		(free(file), free(data->ceiling_rgb_buf),
			free(data->floor_rgb_buf), ft_error("error of allocation\n"));
	while (tmp[idx])
		idx++;
	if (idx != 3)
	{
		(free_map(tmp, idx), free(file), free_txtr_colors(data));
		ft_error("Color format syntax error.\n");
	}
	idx = 0;
	data->file = file;
	while (idx < 3)
	{
		tmp[idx] = ft_trim(tmp[idx]);
		(check_color_range(data, tmp, idx, c), free(tmp[idx]));
		idx++;
	}
	free(tmp);
}

int	check_colors(t_data *data, char *file, char c, int idx)
{
	char	*line;

	data->floor_rgb_buf = create_rgb_buf();
	data->ceiling_rgb_buf = create_rgb_buf();
	while (file[idx] && file[idx] == ' ')
		idx++;
	line = get_line(file + idx, '\n');
	if (!line)
		(free(file), free_txtr_colors(data), ft_error("error of allocation\n"));
	idx += ft_strlen(line);
	parse_color_val(data, line, c, file);
	increasing_flg(data->flg, c);
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
	return (check_flags(flg), ft_strdup(file + i));
}
