#include "../../include/cub3d.h"

void	load_textures(t_mlx *mlx);
void	load_images(t_mlx *mlx);

void	create_window(t_mlx *mlx)
{
	if (mlx->data->columns > mlx->data->max_width
		|| mlx->data->rows > mlx->data->max_height)
		free(mlx->data->rays), ft_error("error: You exceeded the limits of screen\n");
	mlx->ptr = mlx_init(mlx->data->screen_width, mlx->data->screen_height, "cub3D", 0);
	if (!mlx->ptr)
		free(mlx->data->rays), exit(1);
}

void	render_frame_to_window(t_mlx *mlx)
{
	if (mlx_image_to_window(mlx->ptr, mlx->imgs.frame, 0, 0) == -1)
		graceful_exit(mlx, 1);
}

void	init_mlx(t_mlx *mlx)
{
	create_window(mlx);
	load_textures(mlx);
	load_images(mlx);
	render_frame_to_window(mlx);
}