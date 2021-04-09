#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include "libs/minilibx_mms/mlx.h"
# include "libs/libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct s_coords
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
} t_coords;

typedef struct s_matrix{
    char **worldMap;
    int matrixWidth;
    int matrixHeight;
} t_matrix;

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
    t_matrix matrix;
} g_values;

void globs_init();
int drawFrame();
int get_next_line(int fd, char **line);
void matrix_parser(char *filepath);
int matrix_checker();

#endif