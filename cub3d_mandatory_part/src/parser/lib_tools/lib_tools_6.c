/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:38:24 by messkely          #+#    #+#             */
/*   Updated: 2024/12/01 13:42:20 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	go_back(char *file, int i)
{
	if (i <= 0)
		return (0);
	while (i > 0 && file[i] != '\n')
		i--;
	if (file[i] == '\n')
		i++;
	return (i);
}

int	*create_rgb_buf(void)
{
	const int	colors_n = 3;
	int			*rgb_buf;

	rgb_buf = malloc(sizeof(int) * colors_n);
	if (!rgb_buf)
		return (NULL);
	return (rgb_buf);
}

void	free_if_error(t_data *data, char *s, char *str)
{
	free_txtr_paths(data);
	free(s);
	ft_error(str);
}
