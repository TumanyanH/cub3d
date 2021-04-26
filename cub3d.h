#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include "libs/minilibx_mms/mlx.h"
# include "libs/libft/libft.h"
# include "gnl/get_next_line.h"

typedef unsigned int rgb;

typedef struct s_coords
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
} t_coords;

typedef struct		s_norm_print_map
{
	double			cameraX;
	double			rayDirX;
	double			rayDirY;
	int				mapX;
	int				mapY;
	double			sideDistX;
	double			sideDistY;
	double			deltaDistX;
	double			deltaDistY;
	double			perpWallDist;
	int				stepX;
	int				stepY;
	int				hit;
	int				side;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	double			wallX;
	int				texX;
	double			step;
	double			texPos;
	int				texY;
}					t_norm_print_map;

typedef	struct		s_parser
{
	int				res_w;
	int				res_l;

	char			*nor_tex;
	char			*sou_tex;
	char			*wes_tex;
	char			*eas_tex;

	char			*spr_tex;

	rgb				floore_color;
	int				floore_flag;

	rgb				ceilling_color;
	int				ceilling_flag;

	char			**map;

	char			*playr;
	int				playr_x;
	int				playr_y;

	int				size_map;

	int				coll_sprite;
}					t_parser;

typedef struct s_matrix
{
    char **worldMap;
    int matrixWidth;
    int matrixHeight;
} t_matrix;


typedef struct  s_image {
    void        *ptr;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_image;

typedef struct      s_keys {
    int             up;
    int             down;
    int             left;
    int             right;
}                   t_keys;

typedef	struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

struct              s_values
{
    void                *mlx_ptr;
    void                *mlx_win_ptr;
    int                 screen_width;
    int                 screen_height;
    int                 texWidth;
    int                 texHeight;
    double              moveSpeed;
    double              rotSpeed;
    t_coords            currents;
    t_matrix            matrix;
    void                *currentImage;
    t_image             image;
    t_keys              keys;
    int                 *texture[8];
    t_data			    t_n;
	t_data			    t_s;
	t_data			    t_w;
	t_data			    t_e;
	t_data			    t_spr;
	t_data			    data;
    t_parser		    p;
    t_norm_print_map    norm_printf_map;
}                   g_values;

void            globs_init();
int             drawFrame();
int             get_next_line(int fd, char **line);
void            matrix_parser(char *filepath);
int             matrix_checker();
void	        get_sprite_norm();
void	        get_sprite();
void	        error(char *str);

void            my_mlx_pixel_put(t_image data, int x, int y, rgb color);
rgb				get_pixel(t_data *data, int x, int y);

#endif