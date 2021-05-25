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
    }
    else 
        error("Wrong input parameters");
    return 0;
}          