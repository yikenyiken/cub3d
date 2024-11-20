#include "../include/cub3d.h"

void	init_mlx(t_mlx *mlx);
void	set_player_xy(t_player *player, double x, double y);
t_ray	*create_rays(t_mlx *mlx, t_data *data);

void	init_data(t_mlx *mlx, t_data *data)
{
	const int	screen_tile_size = 128;

	// data->rows = 10; // to be set
	// data->columns = 24; // to be set
	data->fov = 60 * (M_PI / 180);
	data->screen_width = screen_tile_size * data->columns;
	data->screen_height = screen_tile_size * data->rows;
	data->tile_size = 24;
	data->map_width = data->tile_size * data->columns;
	data->map_height = data->tile_size * data->rows;
	data->num_rays = data->screen_width;
	data->rays = create_rays(mlx, data);
	// data->ceiling_color = 0xFFE7E383; // to be set
	// data->floor_color = 0xFF30CB7F; // to be set
	// data->wall_no_path = "temp_assets/wall_north.png"; // to be set
	// data->wall_we_path = "temp_assets/wall_west.png"; // to be set
	// data->wall_so_path = "temp_assets/wall_south.png"; // to be set
	// data->wall_ea_path = "temp_assets/wall_east.png"; // to be set
}

void	init_player(t_player *player, t_data *data)
{
	set_player_xy(player, player->x * data->tile_size + (data->tile_size / 2), player->y * data->tile_size + (data->tile_size / 2)); // to be set

	// player->angle = M_PI; // to be set
	player->radius = 4;
	player->move_step = 1;
	player->rotation_step = 1.55 * (M_PI / 180);
	player->color = 0xFF000000;
	player->is_moving = 0;
	player->big_step = 10;
}

void	init_cub3d(t_mlx *mlx)
{
	init_data(mlx, &mlx->data);
	init_player(&mlx->player, &mlx->data);
	init_mlx(mlx);
}
