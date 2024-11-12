#include "../../include/cub3d.h"

double	distance_between_points(double x1, double y1, double x2, double y2);
int		is_wall_hit(t_mlx *mlx, double x, double y);

void	set_horz_intersect_xy(t_ray *ray, double ray_angle, t_mlx *mlx)
{

	int 	ray_facing_up;

	ray_facing_up = ray_angle > M_PI;
	ray->horz_intersect_x = ray->x_intercept;
	ray->horz_intersect_y = ray->y_intercept;

	while ((ray->horz_intersect_x >= (double)0 && ray->horz_intersect_x <= mlx->data->map_width)
		&& (ray->horz_intersect_y >= (double)0 && ray->horz_intersect_y <= mlx->data->map_height))
	{
		if (is_wall_hit(mlx, ray->horz_intersect_x, ray->horz_intersect_y - ray_facing_up))
			break ;
		ray->horz_intersect_x += ray->x_step;
		ray->horz_intersect_y += ray->y_step;
	}
}

void	find_horz_intersection(t_ray *ray, double ray_angle, t_mlx *mlx)
{
	int	ray_facing_up;
	int	ray_facing_right;

	ray_facing_up = ray_angle > M_PI;
	ray_facing_right = ray_angle < (M_PI / 2) || ray_angle > 3 * (M_PI / 2);

	ray->y_intercept = floor(mlx->player.y / mlx->data->tile_size) * mlx->data->tile_size;
	if (!ray_facing_up)
		ray->y_intercept += mlx->data->tile_size;

	ray->x_intercept = mlx->player.x + (ray->y_intercept - mlx->player.y) / tan(ray_angle);

	ray->y_step = mlx->data->tile_size;
	if (ray_facing_up)
		ray->y_step = -ray->y_step;
	
	ray->x_step = mlx->data->tile_size / tan(ray_angle);
	if (ray_facing_right && ray->x_step < 0)
		ray->x_step = -ray->x_step;
	if (!ray_facing_right && ray->x_step > 0)
		ray->x_step = -ray->x_step;
	set_horz_intersect_xy(ray, ray_angle, mlx);
}

void	set_vert_intersect_xy(t_ray *ray, double ray_angle, t_mlx *mlx)
{
	int		ray_facing_right;

	ray_facing_right = ray_angle < (M_PI / 2) || ray_angle > 3 * (M_PI / 2);
	ray->vert_intersect_x = ray->x_intercept;
	ray->vert_intersect_y = ray->y_intercept;

	while ((ray->vert_intersect_x >= (double)0 && ray->vert_intersect_x <= mlx->data->map_width)
		&& (ray->vert_intersect_y >= (double)0 && ray->vert_intersect_y <= mlx->data->map_height))
	{
		if (is_wall_hit(mlx, ray->vert_intersect_x - !ray_facing_right, ray->vert_intersect_y))
			break ;
		ray->vert_intersect_x += ray->x_step;
		ray->vert_intersect_y += ray->y_step;
	}
}

void	find_vert_intersection(t_ray *ray, double ray_angle, t_mlx *mlx)
{
	int	ray_facing_up;
	int	ray_facing_right;

	ray_facing_up = ray_angle > M_PI;
	ray_facing_right = ray_angle < (M_PI / 2) || ray_angle > 3 * (M_PI / 2);

	ray->x_intercept = floor(mlx->player.x / mlx->data->tile_size) * mlx->data->tile_size;
	if (ray_facing_right)
		ray->x_intercept += mlx->data->tile_size;

	ray->y_intercept = mlx->player.y + (ray->x_intercept - mlx->player.x) * tan(ray_angle);

	ray->x_step = mlx->data->tile_size;
	if (!ray_facing_right)
		ray->x_step = -ray->x_step;

	ray->y_step = mlx->data->tile_size * tan(ray_angle);
	if (!ray_facing_up && ray->y_step < 0)
		ray->y_step = -ray->y_step;
	if (ray_facing_up && ray->y_step > 0)
		ray->y_step = -ray->y_step;
	set_vert_intersect_xy(ray, ray_angle, mlx);
}

void	set_ray_distance(t_ray *ray, t_mlx *mlx)
{
	double	horz_distance;
	double	vert_distance;

	horz_distance = distance_between_points(mlx->player.x, mlx->player.y, ray->horz_intersect_x, ray->horz_intersect_y);
	vert_distance = distance_between_points(mlx->player.x, mlx->player.y, ray->vert_intersect_x, ray->vert_intersect_y);
	ray->distance = horz_distance;
	ray->wall_hit_x = ray->horz_intersect_x;
	ray->wall_hit_y = ray->horz_intersect_y;
	ray->is_vertical_hit = 0;
	if (horz_distance > vert_distance)
	{
		ray->wall_hit_x = ray->vert_intersect_x;
		ray->wall_hit_y = ray->vert_intersect_y;
		ray->distance = vert_distance;
		ray->is_vertical_hit = 1;
	}
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
