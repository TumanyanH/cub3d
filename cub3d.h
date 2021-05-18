#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include "libs/minilibx_mms/mlx.h"
# include "libs/libft/libft.h"
# include "gnl/get_next_line.h"

typedef unsigned int rgb;

typedef struct 		s_coords
{
    double 			posX;
    double 			posY;
    double 			dirX;
    double 			dirY;
    double 			planeX;
    double			planeY;
} 					t_coords;

typedef	struct		s_parser
{
	char			*nor_tex;
	char			*sou_tex;
	char			*wes_tex;
	char			*eas_tex;

	char			*spr_tex;

	rgb				floore_color;

	rgb				ceilling_color;

	int				size_map;
}					t_parser;

typedef struct 		s_matrix
{
    char 			**worldMap;
    int 			matrixWidth;
    int 			matrixHeight;
	int 			rows_count;
} 					t_matrix;

typedef struct      s_keys {
    int             up;
    int             down;
	int 			left;
	int 			right;
    int             rot_left;
    int             rot_right;
}                   t_keys;

typedef	struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;


typedef struct 		s_p_flags {
	int 			res;
	int 			tex_n;
	int 			tex_w;
	int 			tex_e;
	int 			tex_s;
	int 			spr;
	int 			ceiling;
	int 			floor;
} 					t_p_flags;

typedef struct 		s_sprite_elem
{
	double 			x;
	double 			y;
	double 			distance;
}					t_sprite_elem;


typedef struct 		s_sprite
{
	int 			count;
	t_sprite_elem 	*sprites;
} 					t_sprite;

struct              s_values
{
	void            *mlx_ptr;
	void            *mlx_win_ptr;
	int             screen_width;
	int             screen_height;
	int             texWidth;
	int             texHeight;
	double          moveSpeed;
	double          rotSpeed;
	t_coords        currents;
	t_matrix        matrix;
	void            *currentImage;
	t_data          image;
	t_keys          keys;
	t_data			t_n;
	t_data			t_s;
	t_data			t_w;
	t_data			t_e;
	t_data			t_spr;
	t_parser		p;
	t_p_flags		parser_flags;
	t_sprite		sprites;
	int 			should_save;
}                   g_values;

void            	globs_init();
int             	drawFrame();
int             	get_next_line(int fd, char **line);
void            	matrix_parser(char *filepath);
int             	matrix_checker();
void	        	get_sprite_norm();
void	        	get_sprite();
void	        	error(char *str);
void 				init_sprites();
void 				sort_sprites();
void 				screenshot();

void            	my_mlx_pixel_put(t_data *data, int x, int y, rgb color);
rgb					get_pixel(t_data *data, int x, int y);
int 				win_close();
#endif