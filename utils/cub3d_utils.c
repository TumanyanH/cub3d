#include "../cub3d.h"

void globs_init()
{
    g_values.screen_width = 0;
    g_values.screen_height = 0;
    g_values.texWidth = 64;
    g_values.texHeight = 64;
    g_values.p.ceilling_color = 0x00ADD8E6;
    g_values.p.floore_color = 0x00000000;
    g_values.currents.posX = 22.0;
    g_values.currents.posY = 11.5;
    g_values.currents.dirX = -1;
    g_values.currents.dirY = 0;
    g_values.currents.planeX = 0;
    g_values.currents.planeY = 0.66;
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
   //g_values.p.nor_tex = "./imgs/1.xpm";
   //g_values.p.sou_tex = "./imgs/1.xpm";
   //g_values.p.wes_tex = "./imgs/1.xpm";
   //g_values.p.eas_tex = "./imgs/1.xpm";
   //g_values.p.spr_tex = "./imgs/sprite.xpm";
}

void            my_mlx_pixel_put(t_image *data,int x, int y, rgb color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int 			win_close()
{
    mlx_destroy_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
    exit(0);
}