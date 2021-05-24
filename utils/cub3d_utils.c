#include "../cub3d.h"

void globs_init()
{
    g_values.texWidth = 64;
    g_values.texHeight = 64;
    g_values.currents.posX = 0;
    g_values.currents.posY = 0;
    g_values.currents.dirX = 0;
    g_values.currents.dirY = 0;
    g_values.currents.planeX = 0;
    g_values.currents.planeY = 0;
    g_values.moveSpeed = 0.1;
    g_values.rotSpeed = 0.05;
    g_values.parser_flags.res = 0;
    g_values.parser_flags.tex_e = 0;
    g_values.parser_flags.tex_s = 0;
    g_values.parser_flags.tex_w = 0;
    g_values.parser_flags.tex_n = 0;
    g_values.parser_flags.spr = 0;
    g_values.parser_flags.ceiling = 0;
    g_values.parser_flags.floor = 0;
    g_values.sprites.count = 0;
    g_values.should_save = 0;
    g_values.p.pos_count = 0;
}

void            my_mlx_pixel_put(t_data *data,int x, int y, rgb color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int 			win_close()
{
    // mlx_destroy_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
    exit(0);
    return 0;
}