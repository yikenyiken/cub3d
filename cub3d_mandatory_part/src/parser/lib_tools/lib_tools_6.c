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
