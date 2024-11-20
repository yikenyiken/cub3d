#include "../../include/cub3d.h"

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
}

void	free_txtr_paths(t_data *data)
{
	free(data->wall_no_path);
	free(data->wall_we_path);
	free(data->wall_so_path);
	free(data->wall_ea_path);
}

void	free_parser_allocations(t_mlx *mlx)
{
	free_map(mlx->data.map, mlx->data.rows);
	free_txtr_paths(&mlx->data);
}

void	graceful_exit(t_mlx *mlx, int code)
{
	free_parser_allocations(mlx);
	free(mlx->data.rays);
	mlx_terminate(mlx->ptr);
	exit(code);
}