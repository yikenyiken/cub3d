/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:11:48 by messkely          #+#    #+#             */
/*   Updated: 2025/01/03 21:27:06 by messkely         ###   ########.fr       */
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
		return (free(s), NULL);
	flg = 0;
	i = 0;
	j = 0;
	while (s[i] && j < 3 && flg < 2)
	{
		if (s[i] && s[i] == c && flg++)
			i++;
		while (s[i] && s[i] == ' ')
			i++;
		arr[j] = ft_substr(s, c, &i, j);
		if (!arr[j])
			return (free(s), free_txtr_paths(data), free_buff(arr, j));
		j++;
	}
	return (free(s), arr[j] = NULL, arr);
}
