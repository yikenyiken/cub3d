/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:22:47 by messkely          #+#    #+#             */
/*   Updated: 2025/01/04 12:04:35 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

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
	int	count;
	int	in_line;

	i = 0;
	count = 0;
	in_line = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (in_line)
			{
				count++;
				in_line = 0;
			}
		}
		else if (s[i] != ' ' && s[i] != '\t')
			in_line = 1;
		i++;
	}
	if (in_line)
		count++;
	return (count);
}

char	*ft_substr(char *s, char c, int *start, int idx)
{
	int		end;
	char	*arr;
	int		i;

	if (!s)
		return (NULL);
	if (c == '\n' && s[*start] == '1' && s[*start - 1] == ' ')
		*start = go_back(s, *start);
	end = *start;
	while (s[end] && s[end] != c)
		end++;
	while (s[end] && c == ',' && idx == 2 && s[end] != '\n')
		end++;
	arr = malloc((end - *start + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[*start] && *start < end)
		arr[i++] = s[(*start)++];
	return (arr[i] = '\0', arr);
}

char	**free_buff(char **buff, int len)
{
	while (len >= 0)
		free(buff[len--]);
	free(buff);
	return (NULL);
}

char	**ft_split(t_data *data, char *s, char c)
{
	char	**arr;
	int		size;
	int		i;
	int		j;

	size = get_size(s, c);
	if (c == '\n')
		data->rows = size;
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (free(s), free_txtr_paths(data), NULL);
	i = 0;
	j = 0;
	while (s[i] && j < size)
	{
		while (s[i] && (s[i] == c || s[i] == ' '))
			i++;
		arr[j] = ft_substr(s, c, &i, j);
		if (!arr[j])
			return (free(s), free_txtr_paths(data), free_buff(arr, j));
		j++;
	}
	return (free(s), arr[j] = NULL, arr);
}
