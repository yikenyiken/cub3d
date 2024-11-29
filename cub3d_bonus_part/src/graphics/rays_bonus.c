/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:01:23 by yiken             #+#    #+#             */
/*   Updated: 2024/11/29 17:19:20 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

double	normalize_angle(double angle);
void	find_horz_intersection(t_ray *ray, double ray_angle, t_mlx *mlx);
void	find_vert_intersection(t_ray *ray, double ray_angle, t_mlx *mlx);
void	set_ray_distance(t_ray *ray, t_mlx *mlx);
void	free_parser_allocations(t_mlx *mlx);

t_ray	*create_rays(t_mlx *mlx, t_data *data)
{
	t_ray	*rays;

	rays = malloc(sizeof(t_ray) * data->num_rays);
	if (!rays)
	{
		write(2, "failed to allocate rays\n", 24);
		free_parser_allocations(mlx);
		exit(1);
	}
	return (rays);
}

void	cast_ray(t_ray *ray, t_mlx *mlx)
{
	find_horz_intersection(ray, ray->angle, mlx);
	find_vert_intersection(ray, ray->angle, mlx);
	set_ray_distance(ray, mlx);
}

void	cast_rays(t_mlx *mlx)
{
	double	ray_angle;
	int		i;

	ray_angle = mlx->player.angle - (mlx->data.fov / 2);
	i = 0;
	while (i < mlx->data.num_rays)
	{
		(mlx->data.rays + i)->angle = normalize_angle(ray_angle);
		cast_ray(mlx->data.rays + i, mlx);
		ray_angle += mlx->data.fov / mlx->data.num_rays;
		i++;
	}
}
