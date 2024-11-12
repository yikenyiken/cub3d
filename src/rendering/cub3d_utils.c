#include "../../include/cub3d.h"

void	frame_put_pixel(t_mlx *mlx, int x, int y, uint32_t color)
{
	uint32_t	*frame_pixel_buffer;

	frame_pixel_buffer = (uint32_t *)mlx->imgs.frame->pixels;

	*(frame_pixel_buffer + (y * (int)mlx->imgs.frame->width) + x) = color; // (y * mlx.img.frame->width) is used to travel to the next row
}

uint32_t	*get_wall_img_pxbuff(t_ray *ray, t_mlx *mlx)
{
	t_player	*player;
	t_imgs		*imgs;
	uint8_t	*wall_img_pixel_buffer;

	player = &mlx->player;
	imgs = &mlx->imgs;

	wall_img_pixel_buffer = imgs->wall_north->pixels; // north by default

	if (ray->is_vertical_hit && ray->wall_hit_x > player->x) // east
		wall_img_pixel_buffer = imgs->wall_east->pixels;

	if (ray->is_vertical_hit && ray->wall_hit_x < player->x) // west
		wall_img_pixel_buffer = imgs->wall_west->pixels;

	if (!ray->is_vertical_hit && ray->wall_hit_y > player->y) // south
		wall_img_pixel_buffer = imgs->wall_south->pixels;
	
	return ((uint32_t *)wall_img_pixel_buffer);
}
