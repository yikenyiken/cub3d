#include "../../../include/cub3d.h"

int	go_back(char *file, int i)
{
	if (i <= 0)
		return (0);
	while (i > 0 && file[i] != '\n')
		i--;
	if (file[i] == '\n')
		i++;
	return (i);
}

int	*create_rgb_buf()
{
	const int	colors_n = 3;
	int			*rgb_buf;

	rgb_buf = malloc(sizeof(int) * colors_n);
	if (!rgb_buf)
		return (NULL);
	return (rgb_buf);
}

void	check_map_dimensions(t_data *data)
{
	const int	max_cols = 100;
	const int	max_rows = 40;

	if (data->columns > max_cols || data->rows > max_rows)
	{
		free_game(data);
		ft_error("map dimensions limit exceeded\n");
	}
}