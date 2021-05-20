#include "cub3d.h"

int key_hook()
{
    char **worldMap = g_values.matrix.worldMap;
    double posX = g_values.currents.posX;
    double posY = g_values.currents.posY;
    double dirX = g_values.currents.dirX;
    double dirY = g_values.currents.dirY;
    double moveSpeed = g_values.moveSpeed;
    
    if (g_values.keys.up) // w
    {
        if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == '0') g_values.currents.posX += dirX * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == '0') g_values.currents.posY += dirY * moveSpeed;
    }
    if (g_values.keys.rot_left) // a
    {
        double oldDirX = g_values.currents.dirX;
        g_values.currents.dirX = g_values.currents.dirX * cos(g_values.rotSpeed) - dirY * sin(g_values.rotSpeed);
        g_values.currents.dirY = oldDirX * sin(g_values.rotSpeed) + dirY * cos(g_values.rotSpeed);
        double oldPlaneX = g_values.currents.planeX;
        g_values.currents.planeX = g_values.currents.planeX * cos(g_values.rotSpeed) - g_values.currents.planeY * sin(g_values.rotSpeed);
        g_values.currents.planeY = oldPlaneX * sin(g_values.rotSpeed) + g_values.currents.planeY * cos(g_values.rotSpeed);
    }
    if (g_values.keys.down) // s
    {
        if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == '0') g_values.currents.posX -= dirX * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == '0') g_values.currents.posY -= dirY * moveSpeed;
    }
    if (g_values.keys.left) // s
    {
        if(worldMap[(int)(posX - dirY * moveSpeed)][(int)(posY)] == '0') g_values.currents.posX -= dirY * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY + dirX * moveSpeed)] == '0') g_values.currents.posY += dirX * moveSpeed;
    }
    if (g_values.keys.right) // s
    {
        if(worldMap[(int)(posX + dirY * moveSpeed)][(int)(posY)] == '0') g_values.currents.posX += dirY * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY - dirX * moveSpeed)] == '0') g_values.currents.posY -= dirX * moveSpeed;
    }
    if (g_values.keys.rot_right) // d
    {
        double oldDirX = g_values.currents.dirX;
        g_values.currents.dirX = g_values.currents.dirX * cos(-g_values.rotSpeed) - dirY * sin(-g_values.rotSpeed);
        g_values.currents.dirY = oldDirX * sin(-g_values.rotSpeed) + dirY * cos(-g_values.rotSpeed);
        double oldPlaneX = g_values.currents.planeX;
        g_values.currents.planeX = g_values.currents.planeX * cos(-g_values.rotSpeed) - g_values.currents.planeY * sin(-g_values.rotSpeed);
        g_values.currents.planeY = oldPlaneX * sin(-g_values.rotSpeed) + g_values.currents.planeY * cos(-g_values.rotSpeed);
    }
    return 0;
}

int key_press_hook (int pressed_key)
{
    if (pressed_key == 13) // w
        g_values.keys.up = 1;        
    if (pressed_key == 0) // a
        g_values.keys.left = 1;
    if (pressed_key == 1) // s
        g_values.keys.down = 1;
    if (pressed_key == 2) // d
        g_values.keys.right = 1;
    if (pressed_key == 123) // d
        g_values.keys.rot_left = 1;
    if (pressed_key == 124) // d
        g_values.keys.rot_right = 1;
    if (pressed_key == 257)
        g_values.moveSpeed = 0.15;
    return 0;
}

int key_release_hook (int pressed_key)
{
    if (pressed_key == 53)
    {
        mlx_destroy_window(g_values.mlx_ptr, g_values.mlx_win_ptr);
        exit(0);
    }
    if (pressed_key == 48)
    {
        system("afplay ./sounds/wake_up.mp3");
    }
    if (pressed_key == 13) // w
        g_values.keys.up = 0;        
    if (pressed_key == 0) // a
        g_values.keys.left = 0;
    if (pressed_key == 1) // s
        g_values.keys.down = 0;
    if (pressed_key == 2) // d
        g_values.keys.right = 0;
    if (pressed_key == 123) // d
        g_values.keys.rot_left = 0;
    if (pressed_key == 124) // d
        g_values.keys.rot_right = 0;
    if (pressed_key == 257)
        g_values.moveSpeed = 0.1;
    return 0;
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
    double posX = g_values.currents.posX, posY = g_values.currents.posY;
    double dirX = g_values.currents.dirX, dirY = g_values.currents.dirY;
    double planeX = g_values.currents.planeX, planeY = g_values.currents.planeY;
    int ZBuffer[g_values.screen_width];
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

        // int texNum = (g_values.matrix.worldMap[mapX][mapY] - '0') - 1; //1 subtracted from it so that texture 0 can be used!

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
                // printf("working as hell!%d\n", y);
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
        ZBuffer[x] = perpWallDist;
        x++;
    }
    for(int i = 0; i < g_values.sprites.count; i++)
    {
        g_values.sprites.sprites[i]->distance = (pow((posX - g_values.sprites.sprites[i]->x), 2.0) + pow((posY - g_values.sprites.sprites[i]->y), 2.0));
        // printf("distance is %f\n")
    }
    sort_sprites();
    for(int i = 0; i < g_values.sprites.count; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = g_values.sprites.sprites[i]->x - posX;
      double spriteY = g_values.sprites.sprites[i]->y - posY;

      double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

      double transformX = invDet * (dirY * spriteX - dirX * spriteY);
      double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = (int)((g_values.screen_width / 2) * (1 + transformX / transformY));

      int spriteHeight = abs((int)(g_values.screen_height / (transformY))); //using 'transformY' instead of the real distance prevents fisheye

      int drawStartY = -spriteHeight / 2 + g_values.screen_height / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + g_values.screen_height / 2;
      if(drawEndY >= g_values.screen_height) drawEndY = g_values.screen_height - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int) (g_values.screen_height / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= g_values.screen_width) drawEndX = g_values.screen_width - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * g_values.texWidth / spriteWidth) / 256;
        if(transformY > 0 && stripe > 0 && stripe < g_values.screen_width && transformY < ZBuffer[stripe])
            for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
            {
            int d = (y) * 256 - g_values.screen_height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
            int texY = ((d * g_values.texHeight) / spriteHeight) / 256;
            if (get_pixel(&g_values.t_spr, texX, texY))
                my_mlx_pixel_put(&g_values.image, stripe, y,  get_pixel(&g_values.t_spr, texX, texY)); //paint pixel if it isn't black, black is the invisible color
            }
      }
    }
    return 1;
}

int func(struct s_values *s)
{
    key_hook();
    clear_screen();
    drawFrame();
    if (g_values.should_save)
        screenshot();
    mlx_put_image_to_window(s->mlx_ptr, s->mlx_win_ptr, s->image.img, 0, 0);
    mlx_do_sync(s->mlx_ptr);
    return (0);
}

int check_arg2(char *str)
{
    int len = ft_strlen(str);
    return (str[len - 1] == 'b'
            && str[len - 2] == 'u'
            && str[len - 3] == 'c'
            && str[len - 4] == '.');
}

int main(int argc, char **argv)
{
    globs_init();
    g_values.mlx_ptr = mlx_init();
    if (argc == 1)
        exit(0);
    //printf("%d, %d\n", check_arg2(argv[1]) , ft_strncmp(argv[2], "--save", 6));
    if ((argc == 2 && check_arg2(argv[1])) || (argc == 3 && check_arg2(argv[1]) && (ft_strncmp(argv[2], "--save", 6) == 0)))
    {
        if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
            g_values.should_save = 1;
        matrix_parser(argv[1]);
        g_values.mlx_win_ptr = mlx_new_window(g_values.mlx_ptr, g_values.screen_width, g_values.screen_height, "cub3d test");
        init_sprites();
        get_sprite();
        g_values.image.img = mlx_new_image(g_values.mlx_ptr, g_values.screen_width, g_values.screen_height);
        g_values.image.addr = mlx_get_data_addr(g_values.image.img, &g_values.image.bits_per_pixel, &g_values.image.line_length, &g_values.image.endian);
        mlx_hook(g_values.mlx_win_ptr, 2, 1L << 0, key_press_hook, &g_values);
        mlx_hook(g_values.mlx_win_ptr, 3, 1L << 0, key_release_hook, &g_values);
        printf("go to hell if you wanna fail me, I'm on this project for more than 2 months:)))\n"); 
        printf("BTW, press tab to hear magic\n");
        mlx_hook(g_values.mlx_win_ptr, 17, 1L << 0, win_close, &g_values);
        mlx_loop_hook(g_values.mlx_ptr, func, &g_values);
        mlx_loop(g_values.mlx_ptr);
        return 0;
    }
}          