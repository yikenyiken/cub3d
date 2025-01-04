/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:51:39 by messkely          #+#    #+#             */
/*   Updated: 2024/12/31 14:12:44 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	ft_error(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	exit(1);
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
	end = ft_strlen(s) - 1;
	while (s[start] && s[start] == ' ')
		start++;
	while (s[end] && s[end] == ' ')
		end--;
	buff = malloc((end - start + 2) * sizeof(char));
	if (!buff)
		return (free(s), NULL);
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

size_t	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	size_t		res;

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
		if ((res * sign) > 2147483647)
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
