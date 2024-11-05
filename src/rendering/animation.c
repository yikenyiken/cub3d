/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:00:22 by messkely          #+#    #+#             */
/*   Updated: 2024/11/04 17:55:03 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*ptr;

	nb = n;
	len = 0;
	if (n == 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	if (nb == 0)
		return (ptr[0] = '0', ptr);
	while (nb)
	{
		ptr[--len] = (nb % 10) + '0';
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
	buff = malloc((ft_strlen(dir) + 7));
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

mlx_image_t	**ft_load_image(t_mlx *mlx, int num_sprites)
{
	int				i;
	char			*filepath;
	mlx_image_t		**buff;
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	buff = malloc(sizeof(mlx_image_t *) * (num_sprites + 2));
	if (!buff)
		return (NULL);
	i = 0;
	while (i < num_sprites)
	{
		filepath = ft_strjoin("sprites/", ft_itoa(i), ".png");
		texture = mlx_load_png(filepath);
		img = mlx_texture_to_image(mlx->ptr, texture);
		mlx_resize_image(img, 1400, 1000);
		buff[i] = img;
		free(filepath);
		mlx_delete_texture(texture);
		i++;
	}
	return (buff[i] = NULL, buff);
}

void	render_imgs(t_mlx *mlx, mlx_image_t **sprites, int n_sprite)
{
	static int	i;

	if (!(mlx->stop))
		sprites[0]->enabled = 1;
	while (i < n_sprite)
	{
		if (mlx_image_to_window(mlx->ptr, sprites[i], 200, 360) < 0)
			(write(2, "Error displaying image\n", 23), exit(1));
		sprites[i]->enabled = 0;
		i++;
	}
}

void	animation(t_mlx *mlx, mlx_image_t **sprites, int n_sprite)
{
	static int	i;
	static int	c;

	mlx->stop = 1;
	sprites[i]->enabled = 0;
	if (c == 1)
	{
		i = (i + 1) % n_sprite;
		c = 0;
		sprites[i]->enabled = 1;
	}
	c++;
}

void	free_game(t_map *map)
{
	int	i;

	i = 0;
	while (map->map3D[i])
		free(map->map3D[i++]);
	free(map->map3D);
	free(map->EApath);
	free(map->NOpath);
	free(map->SOpath);
	free(map->WEpath);
}
