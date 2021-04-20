#include "cub3d.h"

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
    //     {
    //         int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
    //         int ycolor = y * 256 / texHeight;
    //         int xycolor = y * 128 / texHeight + x * 128 / texWidth;
    //         g_values.texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red g_values.texture with black cross
    //         g_values.texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
    //         g_values.texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
    //         g_values.texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
    //         g_values.texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
    //         g_values.texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
    //         g_values.texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient

    //         g_values.texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey g_values.texture
    //     }
    //     printf("%d - freaking awesome\n", x);
    // }
    
}

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
    g_values.moveSpeed = 0.1;
    g_values.rotSpeed = 0.05;
    texture_init();
}

void            my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
