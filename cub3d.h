#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "libs/minilibx_mms/mlx.h"
# include "libs/libft/libft.h"

typedef struct s_coords
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
} t_coords;

struct s_values
{
    void *mlx_ptr;
    void *mlx_win_ptr;
    int screen_width;
    int screen_height;
    int texWidth;
    int texHeight;
    int topColor;
    int bottomColor;
    t_coords currents;
    int **worldMap;
} g_values;

void globs_init();
int drawFrame();
#endif