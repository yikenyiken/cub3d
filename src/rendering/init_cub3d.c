#include "../../include/cub3d.h"

void	init_mlx(t_mlx *mlx);
void	set_player_xy(t_player *player, double x, double y);
t_ray	*create_rays(t_data *data);

void	init_data(t_data *data)
{
	const int	screen_tile_size = 128;

	data->fov = 60 * (M_PI / 180);
	data->max_width = 25;
	data->max_height = 13;
	data->screen_width = screen_tile_size * data->columns;
	data->screen_height = screen_tile_size * data->rows;
	data->tile_size = 24;
	data->map_width = data->tile_size * data->columns;
	data->map_height = data->tile_size * data->rows;
	data->num_rays = data->screen_width;
	data->rays = create_rays(data);
}

void	init_player(t_player *player, t_data *data)
{
	int	tile;

	tile = data->tile_size;
	set_player_xy(player, data->player_pos[0] * tile + (tile / 2), data->player_pos[1] * tile + (tile / 2));
	player->angle = data->player_angle;
	player->radius = 4;
	player->move_step = 1;
	player->rotation_step = 1.55 * (M_PI / 180);
	player->color = 0xFF000000;
	player->is_moving = 0;
	player->big_step = 6;
}

void	init_cub3d(t_mlx *mlx, t_data *data)
{

	mlx->data = data;
	init_data(mlx->data);
	init_player(&mlx->player, mlx->data);
	init_mlx(mlx);
}