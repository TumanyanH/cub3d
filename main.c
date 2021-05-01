#include "cub3d.h"

int key_hook()
{
    // printf("%d\n", pressed_key);
    char **worldMap = g_values.matrix.worldMap;
    double posX = g_values.currents.posX;
    double posY = g_values.currents.posY;
    double dirX = g_values.currents.dirX;
    double dirY = g_values.currents.dirY;
    double moveSpeed = g_values.moveSpeed;
    g_values.rotSpeed = g_values.rotSpeed;
    double rotSpeed = g_values.rotSpeed;
    
    // printf("%f\n", (dirX * moveSpeed));

    
    if (g_values.keys.up) // w
    {
        // printf("%f\n", (dirX * moveSpeed));
        // mlx_clear_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        // printf("%c --- \n", (worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)]));
        if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == '0') g_values.currents.posX += dirX * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == '0') g_values.currents.posY += dirY * moveSpeed;
        // printf("%f\n", posX);
        // g_values.currents.posX += dirX * moveSpeed;
        // drawFrame();
        // mlx_destroy_window()
    }
    if (g_values.keys.left) // a
    {
        // g_values.currents.posY += dirY * moveSpeed;
        // mlx_clear_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        double oldDirX = g_values.currents.dirX;
        g_values.currents.dirX = g_values.currents.dirX * cos(g_values.rotSpeed) - dirY * sin(g_values.rotSpeed);
        g_values.currents.dirY = oldDirX * sin(g_values.rotSpeed) + dirY * cos(g_values.rotSpeed);
        double oldPlaneX = g_values.currents.planeX;
        g_values.currents.planeX = g_values.currents.planeX * cos(g_values.rotSpeed) - g_values.currents.planeY * sin(g_values.rotSpeed);
        g_values.currents.planeY = oldPlaneX * sin(g_values.rotSpeed) + g_values.currents.planeY * cos(g_values.rotSpeed);
        // drawFrame();
    }
    if (g_values.keys.down) // s
    {
        // g_values.currents.posX += dirX * moveSpeed;
        // mlx_clear_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        // printf("%d\n", 5);
        if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == '0') g_values.currents.posX -= dirX * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == '0') g_values.currents.posY -= dirY * moveSpeed;
        // drawFrame();
    }
    if (g_values.keys.right) // d
    {
        // g_values.currents.posY += dirY * moveSpeed;
        // mlx_clear_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        double oldDirX = g_values.currents.dirX;
        g_values.currents.dirX = g_values.currents.dirX * cos(-g_values.rotSpeed) - dirY * sin(-g_values.rotSpeed);
        g_values.currents.dirY = oldDirX * sin(-g_values.rotSpeed) + dirY * cos(-g_values.rotSpeed);
        double oldPlaneX = g_values.currents.planeX;
        g_values.currents.planeX = g_values.currents.planeX * cos(-g_values.rotSpeed) - g_values.currents.planeY * sin(-g_values.rotSpeed);
        g_values.currents.planeY = oldPlaneX * sin(-g_values.rotSpeed) + g_values.currents.planeY * cos(-g_values.rotSpeed);
    }
    // drawFrame();
    // mlx_do_sync(g_values.mlx_ptr);
    return 0;
}

int key_press_hook (int pressed_key)
{
    if (pressed_key == 13 || pressed_key == 126) // w
        g_values.keys.up = 1;        
    if (pressed_key == 0 || pressed_key == 123) // a
        g_values.keys.left = 1;
    if (pressed_key == 1 || pressed_key == 125) // s
        g_values.keys.down = 1;
    if (pressed_key == 2 || pressed_key == 124) // d
        g_values.keys.right = 1;
    if (pressed_key == 257)
        g_values.moveSpeed = 0.15;
    return 0;
}

int key_release_hook (int pressed_key)
{
    printf("%d\n", pressed_key);
    if (pressed_key == 53)
    {
        mlx_destroy_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        exit(0);
    }
    if (pressed_key == 13 || pressed_key == 126) // w
        g_values.keys.up = 0;        
    if (pressed_key == 0 || pressed_key == 123) // a
        g_values.keys.left = 0;
    if (pressed_key == 1 || pressed_key == 125) // s
        g_values.keys.down = 0;
    if (pressed_key == 2 || pressed_key == 124) // d
        g_values.keys.right = 0;
    if (pressed_key == 257)
        g_values.moveSpeed = 0.1;
    return 0;
}

void verLine(int x, int drawStart, int drawEnd, int color)
{
    // int i = 0;
    
    // while (i < drawStart)
    // {
    //     my_mlx_pixel_put(&g_values.image, x, i, g_values.topColor);
    //     i++;
    // }
    // while (i < drawEnd)
    // {
    //     my_mlx_pixel_put(&g_values.image, x, i, color);
    //     i++;
    // }
    // while (i < g_values.screen_height)
    // {
    //     my_mlx_pixel_put(&g_values.image, x, i, g_values.bottomColor);
    //     i++;
    // }

    
}

void drawBuffer(int x, int drawStart, int drawEnd, int** buffer)
{
    // int i = 0;

    // while (i < g_values.screen_height)
    // {
    //     if (i < drawStart)
    //         my_mlx_pixel_put(x, i, g_values.p.ceilling_color);
    //     else if (i >= drawStart && i <= drawEnd)
    //         my_mlx_pixel_put(x, i, buffer[i][x]);
    //     else 
    //         my_mlx_pixel_put(x, i, g_values.p.floore_color);
    //     i++;
    // }
}

void	side_world(int x, int y)
{
	if (y < g_values.norm_printf_map.drawStart)
		my_mlx_pixel_put(&g_values.image, x, y, g_values.p.ceilling_color);
	if (y >= g_values.norm_printf_map.drawStart && y <= g_values.norm_printf_map.drawEnd)
	{
        g_values.norm_printf_map.texY = (int)g_values.norm_printf_map.texPos & (g_values.texHeight - 1);
        g_values.norm_printf_map.texPos += g_values.norm_printf_map.step;
        if (g_values.norm_printf_map.side == 1)
        {
            if (g_values.norm_printf_map.stepY > 0)
                my_mlx_pixel_put(&g_values.image, x, y,
                get_pixel(&g_values.t_n, g_values.norm_printf_map.texX, g_values.norm_printf_map.texY));
            else
                my_mlx_pixel_put(&g_values.image, x, y,
                get_pixel(&g_values.t_n, g_values.norm_printf_map.texX, g_values.norm_printf_map.texY));
        }
        else
        {
            if (g_values.norm_printf_map.stepY > 0)
                my_mlx_pixel_put(&g_values.image, x, y,
                get_pixel(&g_values.t_e, g_values.norm_printf_map.texX, g_values.norm_printf_map.texY));
            else
                my_mlx_pixel_put(&g_values.image, x, y,
                get_pixel(&g_values.t_w, g_values.norm_printf_map.texX, g_values.norm_printf_map.texY));
        }
    }
	if (y > g_values.norm_printf_map.drawEnd && y < g_values.p.res_l)
		my_mlx_pixel_put(&g_values.image, x, y, g_values.p.floore_color);
    // printf("x - %d, y - %d\n", x, *y);
}

void clear_screen()
{
    for (int y = 0; y < g_values.screen_height; y++)
    {
        for (int x = 0; x < g_values.screen_width; x++)
        {
		    my_mlx_pixel_put(&g_values.image, x, y, 0x00000000);
        }
    }
}

int drawFrame()
{
//    printf("%s\n",g_values.p.nor_tex) ;
    double posX = g_values.currents.posX, posY = g_values.currents.posY;
    double dirX = g_values.currents.dirX, dirY = g_values.currents.dirY;
    double planeX = g_values.currents.planeX, planeY = g_values.currents.planeY;
    int buffer[g_values.screen_height][g_values.screen_width];

    // clock_t time = clock();
    // clock_t oldTime = 0;

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
        }
        if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
        
        int lineHeight = (int)(g_values.screen_height/ perpWallDist);
        // printf("%d\n", lineHeight);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = (-1 * lineHeight) / 2 + g_values.screen_height/ 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + g_values.screen_height/ 2;
        if(drawEnd >= g_values.screen_height)drawEnd = g_values.screen_height- 1;
        // if(g_values.norm_printf_map.drawEnd < 0) g_values.norm_printf_map.drawEnd = 0;

        // printf("%d - %d\n", g_values.norm_printf_map.drawStart, g_values.norm_printf_map.drawEnd);

            // int color;
            // switch(g_values.matrix.worldMap[g_values.norm_printf_map.mapX][g_values.norm_printf_map.mapY])
            // {
            //     case '1':
            //         color = 0x00FF0000;
            //         break;
            //     case '2':
            //         color = 0x0000FF00;
            //         break;
            //     case '3':
            //         color = 0x000000FF;
            //         break;
            //     case '4':
            //         color = 0x00FFFFFF;
            //         break;
            //     case '5':
            //         color = 0x00AAAAAA;
            //         break;
            //     default: 
            //         color = 0x00000000;
            //         break; 
            // }

            // if (g_values.norm_printf_map.side == 1) {color = color / 2;}

        int texNum = (g_values.matrix.worldMap[g_values.norm_printf_map.mapX][g_values.norm_printf_map.mapY] - '0') - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = posY + perpWallDist * rayDirY;
      else           wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)g_values.texWidth);
      if(side == 0 && rayDirX > 0) texX = g_values.texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = g_values.texWidth - texX - 1;


        // // // //x coordinate on the texture
        // // Starting texture coordinate
        


        g_values.norm_printf_map.drawStart = drawStart;
        g_values.norm_printf_map.drawEnd = drawEnd;
        // g_values.norm_printf_map.texX = texX;
        // int texX = (int)(g_values.norm_printf_map.wallX * (double)(g_values.texWidth));
        // if(g_values.norm_printf_map.side == 0 && g_values.norm_printf_map.rayDirX > 0) texX = g_values.texWidth - texX - 1;
        // if(g_values.norm_printf_map.side == 1 && g_values.norm_printf_map.rayDirY < 0) texX = g_values.texWidth - texX - 1;
        // g_values.norm_printf_map.step = 1.0 * g_values.texHeight / g_values.norm_printf_map.lineHeight;
        // g_values.norm_printf_map.texPos = (g_values.norm_printf_map.drawStart - g_values.screen_height / 2 + g_values.norm_printf_map.lineHeight / 2) * g_values.norm_printf_map.step;
        
        

		double step = 1.0 * g_values.texHeight / lineHeight;
        // Starting texture coordinate
        double texPos = (drawStart - g_values.screen_height / 2 + lineHeight / 2) * step;
        for (int y = 0; y < drawStart; y++)
            my_mlx_pixel_put(&g_values.image, x, y, g_values.p.ceilling_color);
        for (int y = drawStart; y<drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (g_values.texHeight - 1);
            texPos += step;
            int color = 0;
            // printf("x - %d, y - %d\n", texX, texY);
            if (g_values.norm_printf_map.side == 1)
            {
                if (g_values.norm_printf_map.stepY > 0)
                    color = get_pixel(&g_values.t_e, texX, texY);
                else
                    color = get_pixel(&g_values.t_n, texX, texY);
            }
            else
            {
                if (g_values.norm_printf_map.stepY > 0)
                    color = get_pixel(&g_values.t_e, texX, texY);
                else
                    color = get_pixel(&g_values.t_w, texX, texY);
            }
            my_mlx_pixel_put(&g_values.image, x, y, color);
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            // if(side == 1) color = (color >> 1) & 8355711;
            // buffer[y][x] = color;
        }
        for (int y = drawEnd; y < g_values.screen_height; y++)
            my_mlx_pixel_put(&g_values.image, x, y, g_values.p.floore_color);

        // // // printf("%d\n", drawStart);
        // for(int y = 0; y < g_values.screen_height; y++)
        // {
        //     // if (y < 5)
        //     // {
        //     //     if (x == 0)
        //     //     {
        //     //     }
        //     // }
        //     // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        //     int texY = (int)g_values.norm_printf_map.texPos & (g_values.texHeight - 1);
        //     g_values.norm_printf_map.texPos += g_values.norm_printf_map.step;
        //     // unsigned int color = g_values.texture[texNum][g_values.texHeight * g_values.norm_printf_map.texY + texX];

        //     // printf("x - %d, y - %d\n", texX, texY);
            
        //     if (y < g_values.norm_printf_map.drawStart)
        //         my_mlx_pixel_put(&g_values.image, x, y, g_values.p.ceilling_color);
        //     if (y >= g_values.norm_printf_map.drawStart && y <= g_values.norm_printf_map.drawEnd)
        //     {
        //         texY = (int)g_values.norm_printf_map.texPos & (g_values.texHeight - 1);
        //         g_values.norm_printf_map.texPos += g_values.norm_printf_map.step;
        //         if (g_values.norm_printf_map.side == 1)
        //         {
        //             if (g_values.norm_printf_map.stepY > 0)
        //                 my_mlx_pixel_put(&g_values.image, x, y,
        //                 get_pixel(&g_values.t_n, texX, texY));
        //             else
        //                 my_mlx_pixel_put(&g_values.image, x, y,
        //                 get_pixel(&g_values.t_n, texX, texY));
        //         }
        //         else
        //         {
        //             if (g_values.norm_printf_map.stepY > 0)
        //                 my_mlx_pixel_put(&g_values.image, x, y,
        //                 get_pixel(&g_values.t_e, texX, texY));
        //             else
        //                 my_mlx_pixel_put(&g_values.image, x, y,
        //                 get_pixel(&g_values.t_w, texX, texY));
        //         }
        //     }
        //     if (y > g_values.norm_printf_map.drawEnd && y < g_values.p.res_l)
        //         my_mlx_pixel_put(&g_values.image, x, y, g_values.p.floore_color);
        //     // my_mlx_pixel_put(&g_values.image,x, y, color);
        // }
            
        // verLine(x, g_values.norm_printf_map.drawStart, g_values.norm_printf_map.drawEnd, color); 
        // drawBuffer(x, drawStart, drawEnd, buffer);
                
        // for (int i = 0; i < g_values.screen_height; i++)
        // {
        //     if(i >= drawStart && i <= drawEnd)
        //     {
        //         my_mlx_pixel_put(&g_values.image, x, i, 0x00ff0000);
        //     }
        // }
        // g_values.norm_printf_map.texY = texY;

        // for (int y = 0; y < g_values.screen_height; y++)
        // printf("%d - %d\n", drawStart, drawEnd);
        // if (x > 300)
        //     exit(0);
        x++;
    }
    
    g_values.moveSpeed = g_values.moveSpeed; //the constant value is in squares/second
    g_values.rotSpeed = g_values.rotSpeed; //frameTimeI * 3.0;
    return 1;
}

int func(struct s_values *s)
{
    key_hook();
    clear_screen();
    drawFrame();
    mlx_put_image_to_window(s->mlx_ptr, s->mlx_win_ptr, s->image.ptr, 0, 0);
    mlx_do_sync(s->mlx_ptr);
    return (0);
}
int main()
{
    globs_init();
    g_values.mlx_ptr = mlx_init();
    g_values.mlx_win_ptr = mlx_new_window(g_values.mlx_ptr, g_values.screen_width, g_values.screen_height, "cub3d test");
    matrix_parser("maps/map.cub");
    get_sprite();
    g_values.image.ptr = mlx_new_image(g_values.mlx_ptr, g_values.screen_width, g_values.screen_height);
    g_values.image.addr = mlx_get_data_addr(g_values.image.ptr, &g_values.image.bits_per_pixel, &g_values.image.line_length, &g_values.image.endian);
    // g_values.currentImage = mlx_new_image(g_values.mlx_ptr, g_values.screen_width, g_values.screen_height);
    // drawFrame();
    // mlx_hook(g_values.mlx_win_ptr,2,0, key_hook, &g_values);
    mlx_hook(g_values.mlx_win_ptr, 2, 1L << 0, key_press_hook, &g_values);
    mlx_hook(g_values.mlx_win_ptr, 3, 1L << 0, key_release_hook, &g_values);
    mlx_loop_hook(g_values.mlx_ptr, func, &g_values);
    mlx_loop(g_values.mlx_ptr);
    return 0;
}