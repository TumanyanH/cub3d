#include "cub3d.h"

int key_hook(int pressed_key, void *params)
{
    // printf("%d\n", pressed_key);
    char **worldMap = g_values.matrix.worldMap;
    double posX = g_values.currents.posX;
    double posY = g_values.currents.posY;
    double dirX = g_values.currents.dirX;
    double dirY = g_values.currents.dirY;
    double moveSpeed = g_values.moveSpeed;
    
    if (pressed_key == 53)
    {
        mlx_destroy_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        exit(0);
    }
    else if (pressed_key == 13 || pressed_key == 126) // w
    {
        // printf("%f\n", (dirX * moveSpeed));
        if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0) posX += dirX * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
        mlx_clear_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        // printf("%f\n", posX);
        // g_values.currents.posX -= 0.15;
        drawFrame();
        // mlx_destroy_window()
    }
    else if (pressed_key == 0 || pressed_key == 123) // a
    {
        g_values.currents.posY -= 0.15;
        mlx_clear_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        drawFrame();
    }
    else if (pressed_key == 1 || pressed_key == 125) // s
    {
        g_values.currents.posX += 0.15;
        mlx_clear_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        drawFrame();
    }
    else if (pressed_key == 2 || pressed_key == 124) // d
    {
        g_values.currents.posY += 0.15;
        mlx_clear_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        drawFrame();
    }
    return 0;
}

void verLine(int x, int drawStart, int drawEnd, int color)
{
    int i = 0;
    
    while (i < drawStart)
    {
        my_mlx_pixel_put(&g_values.image, x, i, g_values.topColor);
        i++;
    }
    while (i < drawEnd)
    {
        my_mlx_pixel_put(&g_values.image, x, i, color);
        i++;
    }
    while (i < g_values.screen_height)
    {
        my_mlx_pixel_put(&g_values.image, x, i, g_values.bottomColor);
        i++;
    }
}

int drawFrame()
{
    double posX = g_values.currents.posX, posY = g_values.currents.posY;
    double dirX = g_values.currents.dirX, dirY = g_values.currents.dirY;
    double planeX = g_values.currents.planeX, planeY = g_values.currents.planeY;
    int buffer[g_values.screen_height][g_values.screen_width];

    clock_t time = clock();
    clock_t oldTime = 0;

    int x = 0;
    while (x < g_values.screen_width)
    {
        double cameraX = 2 * x / (double)g_values.screen_width - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;
        int mapX = (int)posX;
        int mapY = (int)posY;
        double sideDistX;
        double sideDistY;
        
        int stepX;
        int stepY;
        int hit = 0;
        int side;
        double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
        double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
        double perpWallDist;
        
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
            if (g_values.matrix.worldMap[mapX][mapY] > '0') 
                hit = 1;

            if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
            else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
            
            int lineHeight = (int)(g_values.screen_height/ perpWallDist);
            // printf("%d\n", lineHeight);

            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = (-1 * lineHeight) / 2 + g_values.screen_height/ 2;
            if(drawStart < 0)drawStart = 0;
            int drawEnd = lineHeight / 2 + g_values.screen_height/ 2;
            if(drawEnd >= g_values.screen_height)drawEnd = g_values.screen_height- 1;

            int color;
            switch(g_values.matrix.worldMap[mapX][mapY])
            {
                case '1':
                    color = 0x00FF0000;
                    break;
                case '2':
                    color = 0x0000FF00;
                    break;
                case '3':
                    color = 0x000000FF;
                    break;
                case '4':
                    color = 0x00FFFFFF;
                    break;
                default: 
                    color = 0x00000000;
                    break; 
            }

            if (side == 1) {color = color / 2;}
            // printf("%d\n", drawStart);
            verLine(x, drawStart, drawEnd, color);
        }
        x++;
    }
    mlx_put_image_to_window(g_values.mlx_ptr, g_values.mlx_win_ptr, g_values.image.ptr, 0, 0);
    oldTime = time;
    time = clock();
    clock_t frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // printf("%d\n", (1.0 / frameTime)); //FPS counter
    // redraw();
    // cls();

    //speed modifiers
    g_values.moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    g_values.rotSpeed = frameTime * 3.0;
    return 1;
}

int main()
{
    globs_init();
    g_values.mlx_ptr = mlx_init();
    g_values.mlx_win_ptr = mlx_new_window(g_values.mlx_ptr, g_values.screen_width, g_values.screen_height, "cub3d test");

    matrix_parser("maps/map.cub");

    g_values.image.ptr = mlx_new_image(g_values.mlx_ptr, g_values.screen_width, g_values.screen_height);
    g_values.image.addr = mlx_get_data_addr(g_values.image.ptr, &g_values.image.bits_per_pixel, &g_values.image.line_length, &g_values.image.endian);
    g_values.currentImage = mlx_new_image(g_values.mlx_ptr, g_values.screen_width, g_values.screen_height);
    drawFrame();
    mlx_key_hook(g_values.mlx_win_ptr, key_hook, &g_values);
    mlx_loop(g_values.mlx_ptr);
    return 0;
}