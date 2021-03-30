#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "libs/minilibx_mms/mlx.h"
# include "libs/libft/libft.h"

struct s_values
{
    void *mlx_ptr;
    void *mlx_win_ptr;
    int screen_width;
    int screen_height;
    int texWidth;
    int texHeight;
} g_values;

typedef struct s_coords
{
    int x;
    int y;
} t_coords;

void globs_init();

#endif