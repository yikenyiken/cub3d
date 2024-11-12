#include "../../include/cub3d.h"

void	cast_ray(t_ray *ray, t_mlx *mlx);
double	normalize_angle(double angle);
double	max(double a, double b);
void	frame_put_pixel(t_mlx *mlx, int x, int y, uint32_t color);

t_ray	*create_rays(t_data *data)
{
	t_ray	*rays;

	rays = malloc(sizeof(t_ray) * data->num_rays);
	if (!rays)
		write(2, "failed to allocate rays\n", 24), exit(1);
	return (rays);
}

void	draw_ray(t_mlx *mlx, t_ray *ray, uint32_t ray_color)
{
	double	dx;
	double	dy;
	double	steps;
	double	x_inc;
	double	y_inc;
	int		i;

	dx = ray->wall_hit_x - mlx->player.x;
	dy = ray->wall_hit_y - mlx->player.y;
	steps = max(fabs(dx), fabs(dy));
	x_inc = dx / steps;
	y_inc = dy / steps;
	i = 0;
	while (i < round(steps))
	{
		int x = floor(mlx->player.x + (x_inc * i));
		int y = floor(mlx->player.y + (y_inc * i));
		frame_put_pixel(mlx, x, y, ray_color);
		i++;
	}
}

void	draw_rays(t_mlx *mlx)
{
	uint32_t	ray_color;
	int			i;

	ray_color = mlx->data->ceiling_color;
	i = 0;
	while (i < mlx->data->num_rays)
	{
		draw_ray(mlx, mlx->data->rays + i, ray_color);
		i++;
	}
}

void	cast_rays(t_mlx *mlx)
{
	double	ray_angle;
	int			i;

	ray_angle = mlx->player.angle - (mlx->data->fov / 2); // since fov == 60deg, you want half of your fov
	//to the right of the direction you are looking at (player.angle), and let's consider the angle of the
	//first ray: player.angle - half of fov
	i = 0;
	while (i < mlx->data->num_rays)
	{
		(mlx->data->rays + i)->angle = normalize_angle(ray_angle);
		cast_ray(mlx->data->rays + i, mlx);
		ray_angle += mlx->data->fov / mlx->data->num_rays; // after fiding the angle of the first ray (ray_angle)
		//you want an increment by which you will advance to get the angle of the second ray (second_ray_angle),
		//at the same time you don't want to surpass fov 60deg so that ray_angle + (incerement * num_rays) == fov (60deg)
		i++;
	}
}