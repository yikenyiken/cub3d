#include "../../include/cub3d.h"

void	vertical_move_listen(t_mlx *mlx, t_player *player);
void	horizontal_move_listen(t_mlx *mlx, t_player *player);
void	upwards_diagonal_move_listen(t_mlx *mlx, t_player *player);
void	downwards_diagonal_move_listen(t_mlx *mlx, t_player *player);
void	game_exit_listen(t_mlx *mlx);
int		is_wall_hit(t_mlx *mlx, double x, double y);
void	frame_put_pixel(t_mlx *mlx, int x, int y, uint32_t color);

void	draw_player(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -(mlx->player.radius);
	while (y <= mlx->player.radius)
	{
		x = -(mlx->player.radius);
		while (x <= mlx->player.radius)
		{
			if (x * x + y * y <= mlx->player.radius * mlx->player.radius)
				frame_put_pixel(mlx, mlx->player.x + x, mlx->player.y + y, mlx->player.color);
			x++;
		}
		y++;
	}
}

void	set_player_xy(t_player *player, double x, double y)
{
	player->x = x;
	player->y = y;
}

void	update_player_by_events(t_mlx *mlx, t_player *player)
{
	double	x_ahead;
	double	y_ahead;
	double	new_x;
	double	new_y;

	if (!player->is_moving)
		return ;

	player->is_moving = 0;
	new_x = player->x + cos(player->new_angle) * player->move_step;
	new_y = player->y + sin(player->new_angle) * player->move_step;

	x_ahead = player->x + cos(player->new_angle) * player->big_step;
	y_ahead = player->y + sin(player->new_angle) * player->big_step;
	
	if (!is_wall_hit(mlx, x_ahead, y_ahead))
		set_player_xy(&mlx->player, new_x, new_y);
}

void	update_player_on_keypress(t_mlx *mlx)
{
	vertical_move_listen(mlx, &mlx->player);
	horizontal_move_listen(mlx, &mlx->player);

	upwards_diagonal_move_listen(mlx, &mlx->player);
	downwards_diagonal_move_listen(mlx, &mlx->player);

	update_player_by_events(mlx, &mlx->player);

	game_exit_listen(mlx);
}