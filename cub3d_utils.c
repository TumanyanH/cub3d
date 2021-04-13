#include "cub3d.h"

void globs_init()
{
    g_values.screen_width = 1920;
    g_values.screen_height = 1080;
    g_values.texWidth = 64;
    g_values.texHeight = 64;
    g_values.topColor = 0x00FFFF00;
    g_values.bottomColor = 0x00000000;
    g_values.currents.posX = 22.0;
    g_values.currents.posY = 11.5;
    g_values.currents.dirX = -1;
    g_values.currents.dirY = 0;
    g_values.currents.planeX = 0;
    g_values.currents.planeY = 0.66;
}

void            my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}