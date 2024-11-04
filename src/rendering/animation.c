/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:00:22 by messkely          #+#    #+#             */
/*   Updated: 2024/10/29 12:48:46 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

mlx_image_t **ft_load_image(t_mlx *mlx, int num_sprites)
{
    mlx_image_t **buff = malloc(sizeof(mlx_image_t *) * (num_sprites + 2));
    if (!buff)
        return (NULL);

    int i = 0;
    char *filepath;
    
    while (i < num_sprites)
    {
        filepath = ft_strjoin("sprites/", ft_itoa(i), ".png");
        mlx_texture_t *texture = mlx_load_png(filepath);
        if (!texture)
        {
            write(2, "Error loading texture\n", 22);
            for (int j = 0; j < i; j++)
                mlx_delete_image(mlx->ptr, buff[j]);
            free(buff);
            exit(1);
        }
        mlx_image_t *img = mlx_texture_to_image(mlx->ptr, texture);
        if (!img)
        {
            write(2, "Error creating image\n", 21);
            mlx_delete_texture(texture);
            for (int j = 0; j < i; j++)
                mlx_delete_image(mlx->ptr, buff[j]);
            free(buff);
            exit(1);
        }
        mlx_resize_image(img, 1400, 1000);
        buff[i] = img;
		free(filepath);
        mlx_delete_texture(texture);
        i++;
    }
    buff[i] = NULL;
    return buff;
}

void render_imgs(t_mlx *mlx, mlx_image_t **sprites, int n_sprite)
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

void animation(t_mlx *mlx, mlx_image_t **sprites, int n_sprite)
{
	static int	i;
	static int	c;
	
	mlx->stop = 1;
	sprites[i]->enabled = 0;
	if (c == 1)
		(i = (i + 1) % n_sprite, c = 0, sprites[i]->enabled = 1);
	
	c++;
}

void	free_game(t_map *map)
{
	int i;

	i = 0;
	while (map->map3D[i])
		free(map->map3D[i++]);
	free(map->map3D);
	free(map->EApath);
	free(map->NOpath);
	free(map->SOpath);
	free(map->WEpath);
}
