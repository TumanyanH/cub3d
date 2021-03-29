#include "cub3d.h"

int key_hook(int pressed_key, void *params)
{
    if (pressed_key == 53)
    {
        mlx_destroy_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        exit(0);
    }
    
    return 0;
}

int main()
{
    t_coords center;
    void *img;
    double posX = 22, posY = 12;
    double dirX = -1, dirY = 0;
    double planeX = 0, planeY = 0.66;

    double time = 0;
    double oldTime = 0;

    globs_init();
    center.x = 100;
    center.y = 100;
    g_values.mlx_ptr = mlx_init();
    g_values.mlx_win_ptr = mlx_new_window(g_values.mlx_ptr, g_values.screen_width, g_values.screen_height, "OpenGL Test");
    mlx_key_hook(g_values.mlx_win_ptr, key_hook, &g_values);
    // img = mlx_png_file_to_image(g_values.mlx_ptr, path, &img_width, &img_height);
    // put_circle(center, 50);
    int x = 0;
    int w = 24;
    while (x < w)
    {
        double cameraX = 2 * x / (double)w - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;
        // double deltaDistX = abs(1 / rayDirX); 
        // double deltaDistY = abs(1 / rayDirY);
        int mapX = (int)posX;
        int mapY = (int)posY;
        double sideDistX;
        double sideDistY;

        // double deltaDistX = abs(1 / rayDirX);
        // double deltaDistY = abs(1 / rayDirY);
        int stepX;
        int stepY;
        int hit = 0;
        int side;
        double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : abs(1 / rayDirX));
        double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : abs(1 / rayDirY));
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (exampleMap[mapX][mapY] > 0) 
                hit = 1;
        } 
        double perpWallDist;
        x++;
    }
    mlx_loop(g_values.mlx_ptr);
}