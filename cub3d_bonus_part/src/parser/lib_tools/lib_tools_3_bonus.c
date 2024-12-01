/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_3_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:47:29 by messkely          #+#    #+#             */
/*   Updated: 2024/12/01 17:38:31 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	init_parse_data(t_data *data, t_flg *flg)
{
	flg->n_flg = 0;
	flg->s_flg = 0;
	flg->w_flg = 0;
	flg->e_flg = 0;
	flg->f_flg = 0;
	flg->c_flg = 0;
	flg->break_flg = 0;
	data->wall_no_path = NULL;
	data->wall_so_path = NULL;
	data->wall_we_path = NULL;
	data->wall_ea_path = NULL;
	data->ceiling_rgb_buf = NULL;
	data->floor_rgb_buf = NULL;
}

char	*get_line(char *s, char c)
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
	{
		arr[i] = s[i];
		i++;
	}
	return (arr[i] = '\0', arr);
}

void	convert_rgb_to_hex(t_data *data, int color_buff[3], char c)
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
		data->floor_color = (a << 24) | (b << 16) | (g << 8) | r;
	else if (c == 'C')
		data->ceiling_color = (a << 24) | (b << 16) | (g << 8) | r;
}

void	increasing_flg(t_flg *flg, char vector)
{
	if (vector == 'N')
		flg->n_flg++;
	if (vector == 'S')
		flg->s_flg++;
	if (vector == 'W')
		flg->w_flg++;
	if (vector == 'E')
		flg->e_flg++;
	if (vector == 'F')
		flg->f_flg++;
	if (vector == 'C')
		flg->c_flg++;
	if (flg->n_flg && flg->s_flg && flg->w_flg && flg->e_flg
		&& flg->f_flg && flg->c_flg)
		flg->break_flg = 1;
}

void	check_flags(t_flg *flg)
{
	if (flg->n_flg != 1 || flg->s_flg != 1 || flg->w_flg != 1
		|| flg->e_flg != 1 || flg->f_flg != 1
		|| flg->c_flg != 1)
		ft_error("configuration file is poorly constructed\n");
}
