/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:01:23 by yiken             #+#    #+#             */
/*   Updated: 2024/11/25 16:16:28 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	// the steps that are taken to find the horizontal/vertical intersection are as follows:
		// calculate the x_intercept (check code)
		// calculate the y_intercept (check code)
		// calculate the x_step (check code)
		// calculate the y_step (check code)
		// increment x_intercept by x_step & y_intercept by y_step until a wall is hit
		// ps: x_step & y_step can be negative depending on the direction the ray is facing
}

void	cast_rays(t_mlx *mlx)
{
	double	ray_angle;
	int		i;

	ray_angle = mlx->player.angle - (mlx->data.fov / 2); // since fov == 60deg, you want half of your fov
	//to the right of the direction you are looking at (player.angle), and let's consider the angle of the
	//first ray: player.angle - half of fov
	i = 0;
	while (i < mlx->data.num_rays)
	{
		(mlx->data.rays + i)->angle = normalize_angle(ray_angle);
		cast_ray(mlx->data.rays + i, mlx);
		ray_angle += mlx->data.fov / mlx->data.num_rays; // after fiding the angle of the first ray (ray_angle)
		//you want an increment by which you will advance to get the angle of the second ray (second_ray_angle),
		//at the same time you don't want to surpass fov 60deg so that ray_angle + (incerement * num_rays) == fov (60deg)
		i++;
	}
}
