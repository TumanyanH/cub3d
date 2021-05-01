#include "../cub3d.h"

unsigned	int	get_pixel(t_data *data, int x, int y)
{
	unsigned int	color;
	char			*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}