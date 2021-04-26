#include "../cub3d.h"

rgb	get_pixel(t_data *data, int x, int y)
{
	rgb				color;
	char			*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(rgb*)dst;
	return (color);
}