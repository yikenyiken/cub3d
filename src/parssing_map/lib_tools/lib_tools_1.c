/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:22:47 by messkely          #+#    #+#             */
/*   Updated: 2024/11/03 10:44:38 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	get_size(char *s, char c)
{
	int	i;
	int	flg;
	int	count;

	i = 0;
	count = 0;
	flg = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && !flg)
		{
			flg = 1;
			count++;
		}
		if (s[i] != c && flg)
			flg = 0;
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

static char	*ft_substr(char *s, char c, int *start)
{
	int		end;
	char	*arr;
	int		i;

	if (!s)
		return (NULL);
	end = *start;
	while (s[end] && s[end] != c)
		end++;
	arr = malloc((end - *start + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	end = *start;
	while (s[end] && s[end] != c)
		arr[i++] = s[end++];
	*start = end;
	return (arr[i] = '\0', arr);
}

char	**free_buff(char **buff, int len)
{
	while (len >= 0)
		free(buff[len--]);
	return (NULL);
}

char	**ft_split(t_map *my_map, char *s, char c)
{
	char	**arr;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = get_size(s, c);
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i] && j < size)
	{
		while (s[i] && s[i] == c)
			i++;
		arr[j] = ft_substr(s, c, &i);
		if (!arr[j])
			return (free_buff(arr, j));
		j++;
	}
	if (c == '\n')
		my_map->rows_size = j;
	return (arr[j] = NULL, arr);
}
