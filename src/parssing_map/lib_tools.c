/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:22:47 by messkely          #+#    #+#             */
/*   Updated: 2024/10/29 12:43:35 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	ft_error(char *s)
{
	write(2, "Error: ", 7);
	write(2, s, ft_strlen(s));
	exit(1);
}

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
			(flg = 1, count++);
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

char	**ft_split(t_map *my_map, char *s, char c)
{
	char	**arr;
	int		size;
	int		i;
	int		j;

	(i = 0, j = 0, size = get_size(s, c));
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && j < size)
	{
		arr[j] = ft_substr(s, c, &i);
		if (!arr[j])
		{
			while (j >= 0)
				free(arr[j--]);
			return (NULL);
		}
		j++;
		while (s[i] && s[i] == c)
			i++;
	}
	if (c == '\n')
		my_map->rows_size = j;
	return (arr[j] = NULL, arr);
}

char	*ft_trim(char *s)
{
	int		start;
	int		end;
	int		i;
	char	*buff;

	if (!s)
		return (NULL);
	start = 0;
	end =  ft_strlen(s) - 1;
	while (s[start] && s[start] ==  ' ')
		start++;
	while (s[end] && s[end] ==  ' ')
		end--;
	buff = malloc((end - start + 2) * sizeof(char));
	if (!buff)
		return (NULL);
	i = 0;
	while (start < end + 1)
		buff[i++] = s[start++];
	buff[i] = '\0';
	return (free(s), buff);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' && str[i])
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + (str[i++] - 48);
		if ((res * sign) < -2147483648 && (res * sign) > 2147483647)
			return (2147483649);
	}
	return (sign * res);
}


int	is_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || !*s)
		return (0);
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}


char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*digits;
	char	*ptr;

	digits = "0123456789";
	(nb = n, len = 0);
	if (n == 0)
		len = 1;
	while (n != 0)
		(n /= 10, len++);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	if (nb == 0)
		return (ptr[0] = '0', ptr);
	while (nb)
	{
		ptr[--len] = digits[nb % 10];
		nb /= 10;
	}
	return (ptr);
}

char	*ft_strjoin(char *dir, char *src, char *extension)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	if (!src)
		return (NULL);
	buff =  malloc((ft_strlen(dir) + 7));
	if (!buff)
		return (NULL);
	j = 0;
	while (dir[j])
		buff[i++] = dir[j++];
	j = 0;
	while (src[j])
		buff[i++] = src[j++];
	j = 0;
	while (extension[j])
		buff[i++] = extension[j++];
	buff[i] = '\0';
	return (free(src), buff);
	
}
