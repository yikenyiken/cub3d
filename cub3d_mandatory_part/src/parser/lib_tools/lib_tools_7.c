/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:55:47 by messkely          #+#    #+#             */
/*   Updated: 2025/01/04 14:59:56 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

char	*ft_substr(char *s, char c, int *start, int idx);

char	**ft_split_colors(t_data *data, char *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		flg;

	arr = malloc((3 + 1) * sizeof(char *));
	if (!arr)
		return (free(s), free_txtr_paths(data), NULL);
	flg = 0;
	i = 0;
	j = 0;
	while (s[i] && j < 3 && flg < 2)
	{
		if (s[i] && s[i] == c)
		{
			i++;
			flg++;
		}
		while (s[i] && s[i] == ' ')
			i++;
		arr[j] = ft_substr(s, c, &i, j);
		if (!arr[j++])
			return (free(s), free_txtr_paths(data), free_buff(arr, j--));
	}
	return (free(s), arr[j] = NULL, arr);
}
