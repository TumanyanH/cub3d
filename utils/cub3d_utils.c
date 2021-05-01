#include "../cub3d.h"

void texture_init()
{
    // unsigned int buffer[g_values.screen_height][g_values.screen_width]; // y-coordinate first because it works per scanline
    
    // for(int i = 0; i < 8; i++) g_values.texture[i] = (int *)malloc((g_values.texWidth * g_values.texHeight));
    // //generate some textures

    // int texWidth = g_values.texWidth;
    // int texHeight = g_values.texHeight;
    // for(int x = 0; x < texWidth; x++)
    // {
    //     for(int y = 0; y < texHeight; y++)
        // {
            // int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
            // int ycolor = y * 256 / texHeight;
            // int xycolor = y * 128 / texHeight + x * 128 / texWidth;
    g_values.texture[0] = mlx_xpm_file_to_image(g_values.mlx_ptr, "./images/1.xpm", &g_values.texWidth, &g_values.texHeight);
    g_values.texture[1] = mlx_xpm_file_to_image(g_values.mlx_ptr, "./images/1.xpm", &g_values.texWidth, &g_values.texHeight);
    g_values.texture[2] = mlx_xpm_file_to_image(g_values.mlx_ptr, "./images/1.xpm", &g_values.texWidth, &g_values.texHeight);
    g_values.texture[3] = mlx_xpm_file_to_image(g_values.mlx_ptr, "./images/1.xpm", &g_values.texWidth, &g_values.texHeight);
    g_values.texture[4] = mlx_xpm_file_to_image(g_values.mlx_ptr, "./images/1.xpm", &g_values.texWidth, &g_values.texHeight);
    g_values.texture[5] = mlx_xpm_file_to_image(g_values.mlx_ptr, "./images/1.xpm", &g_values.texWidth, &g_values.texHeight);
    g_values.texture[6] = mlx_xpm_file_to_image(g_values.mlx_ptr, "./images/1.xpm", &g_values.texWidth, &g_values.texHeight);

            // g_values.texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey g_values.texture
    //     }
    //     // printf("%d - freaking awesome\n", x);
    // }

    // for (int x = 0; x < g_values.texHeight; x++)
    
}

void globs_init()
{
    g_values.screen_width = 1920;
    g_values.screen_height = 1080;
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
    g_values.p.nor_tex = "./imgs/1.xpm";
    g_values.p.sou_tex = "./imgs/1.xpm";
    g_values.p.wes_tex = "./imgs/1.xpm";
    g_values.p.eas_tex = "./imgs/1.xpm";
    g_values.p.spr_tex = "./imgs/1.xpm";
    // texture_init();
}

void            my_mlx_pixel_put(t_image *data,int x, int y, rgb color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
