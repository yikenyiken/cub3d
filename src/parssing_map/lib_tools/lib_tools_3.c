/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:47:29 by messkely          #+#    #+#             */
/*   Updated: 2024/11/05 14:52:21 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D.h"

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

void	convert_rgb_to_hex(t_map *map, int color_buff[3], char c)
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

void	increasing_flg(t_flg *flg, char vector)
{
	if (vector == 'N')
		flg->N_flg++;
	if (vector == 'S')
		flg->S_flg++;
	if (vector == 'W')
		flg->W_flg++;
	if (vector == 'E')
		flg->E_flg++;
	if (vector == 'F')
		flg->F_flg++;
	if (vector == 'C')
		flg->C_flg++;
	if (flg->N_flg && flg->S_flg && flg->W_flg && flg->E_flg
		&& flg->F_flg && flg->C_flg)
		flg->break_flg = 1;
}

void	check_flags(t_flg *flg)
{
	if (flg->N_flg != 1 || flg->S_flg != 1 || flg->W_flg != 1
		|| flg->E_flg != 1 || flg->F_flg != 1
		|| flg->C_flg != 1)
		(printf("%d\n", flg->F_flg), ft_error("check data\n"));
}
