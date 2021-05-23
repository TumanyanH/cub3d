#include "cub3d.h"

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
    double posX = g_values.currents.posX, posY = g_values.currents.posY;
    double dirX = g_values.currents.dirX, dirY = g_values.currents.dirY;
    double planeX = g_values.currents.planeX, planeY = g_values.currents.planeY;
    double ZBuffer[g_values.screen_width];
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
        double deltaDistX =  fabs(1 / rayDirX);
        double deltaDistY =  fabs(1 / rayDirY);
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
            if (g_values.matrix.worldMap[mapX][mapY] == '1') 
                hit = 1;
        }
        if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
        
        int lineHeight = (int)(g_values.screen_height/ perpWallDist);

        int drawStart = (-1 * lineHeight) / 2 + g_values.screen_height/ 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + g_values.screen_height/ 2;
        if(drawEnd >= g_values.screen_height)drawEnd = g_values.screen_height- 1;

        double wallX;
        if (side == 0) wallX = posY + perpWallDist * rayDirY;
        else           wallX = posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        int texX = (int)(wallX * (double)g_values.texWidth);
        if(side == 0 && rayDirX > 0) texX = g_values.texWidth - texX - 1;
        if(side == 1 && rayDirY < 0) texX = g_values.texWidth - texX - 1;
        
		double step = 1.0 * g_values.texHeight / lineHeight;
        double texPos = (drawStart - g_values.screen_height / 2 + lineHeight / 2) * step;
        for (int y = 0; y < drawStart; y++)
            my_mlx_pixel_put(&g_values.image, x, y, g_values.p.ceilling_color);
        for (int y = drawStart; y<drawEnd; y++)
        {
            int texY = (int)texPos & (g_values.texHeight - 1);
            texPos += step;
            int color = 0;

            if (side == 0)
            {
                if (stepX > 0)
                    color = get_pixel(&g_values.t_n , texX, texY);
                else
                    color = get_pixel(&g_values.t_s, texX, texY);
            }
            else
            {
                if (stepY > 0)
                    color = get_pixel(&g_values.t_e, texX, texY);
                else
                    color = get_pixel(&g_values.t_w, texX, texY);;

            }
            my_mlx_pixel_put(&g_values.image, x, y, color);
        }
        for (int y = drawEnd; y < g_values.screen_height; y++)                    
            my_mlx_pixel_put(&g_values.image, x, y, g_values.p.floore_color);
        // printf("%d - perpWallDist\n",perpWallDist);
        ZBuffer[x] = perpWallDist;
        x++;
    }
    for(int i = 0; i < g_values.sprites.count; i++)
    {
        g_values.sprites.sprites[i]->distance = ((posX - g_values.sprites.sprites[i]->x) * ((posX - g_values.sprites.sprites[i]->x) + (posY - g_values.sprites.sprites[i]->y) * (posY - g_values.sprites.sprites[i]->y)));
    }
    sort_sprites();
    for(int i = 0; i < g_values.sprites.count; i++)
    {
        double spriteX = g_values.sprites.sprites[i]->x - posX;
        double spriteY = g_values.sprites.sprites[i]->y - posY;

        double invDet = 1.0 / (planeX * dirY - dirX * planeY); 

        double transformX = invDet * (dirY * spriteX - dirX * spriteY);
        double transformY = invDet * (-planeY * spriteX + planeX * spriteY); 

        int spriteScreenX = (int)((g_values.screen_width / 2) * (1 + transformX / transformY));

        int spriteHeight = abs((int)(g_values.screen_height / (transformY)));

        int drawStartY = -spriteHeight / 2 + g_values.screen_height / 2;
        if(drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + g_values.screen_height / 2;
        if(drawEndY >= g_values.screen_height) drawEndY = g_values.screen_height - 1;

        int spriteWidth = abs((int)(g_values.screen_height / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if(drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if(drawEndX >= g_values.screen_width) drawEndX = g_values.screen_width - 1;
        // printf("exited with drawStartX%d drawEndX%d\n for sprite[%d]\n", drawStartX, drawEndX, i);
        // printf("exited with drawStartY%d drawEndY%d\n for sprite[%d]\n", drawStartY, drawEndY, i);
        for(int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * g_values.texWidth / spriteWidth) / 256;
            //printf("selecting texX%d for sprite[%d]\n", texX, i);
                //             if (i == 0)
                // printf("i've been wondering if you'd...\n");
            // if (i == 0)
            // printf("conditions: %d && %d && %d && %d --- %d\n", transformY > 0, stripe > 0, stripe < g_values.screen_width, transformY < ZBuffer[stripe], ZBuffer[stripe]);
            if(transformY > 0 && stripe > 0 && stripe < g_values.screen_width && transformY < ZBuffer[stripe])
            {
                // if (i == 0)
                // printf("hello, it's me...\n");
                for(int y = drawStartY; y < drawEndY; y++) 
                {
                    int d = (y) * 256 - g_values.screen_height * 128 + spriteHeight * 128;
                    int texY = ((d * g_values.texHeight) / spriteHeight) / 256;
                    // if (i == 0)
                        // printf("selecting texY%d for sprite[%d]\n", texY, i);
                    if (get_pixel(&g_values.t_spr, texX, texY))
                        my_mlx_pixel_put(&g_values.image, stripe, y,  get_pixel(&g_values.t_spr, texX, texY));
                }
            }
        }
    }
    // exit(0);
    return 1;
}