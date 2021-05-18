#include "../cub3d.h"

static	void	fill_screen(int fd)
{
	int i;
	int j;
	int color;

	i = g_values.screen_height ;
	while (--i >= 0)
	{
		j = -1;
		while (++j < g_values.screen_width)
		{
			color = get_pixel(&g_values.image, j, i);
			write(fd, &color, 4);
		}
	}
	exit(0);
}

static	void	screenshot_norm_two(int fd, int all_pix, int zero, int size)
{
	write(fd, &zero, 4);
	write(fd, &size, 4);
	all_pix = 1000;
	write(fd, &all_pix, 4);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
}

static	void	screenshot_norm_one(int fd)
{
	short	plane;

	plane = 1;
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

void			screenshot()
{
	int		fd;
	int		all_pix;
	int		zero;
	int		pos_pix;
	int		size;

	fd = open("screen.bmp", O_CREAT | O_RDWR, 0666);
	all_pix = g_values.screen_width * g_values.screen_height * 4 + 54;
	zero = 0;
	pos_pix = 54;
	size = g_values.screen_width * g_values.screen_height;
	write(fd, "BM", 2);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pix, 4);
	pos_pix = 40;
	write(fd, &pos_pix, 4);
	write(fd, &g_values.screen_width, 4);
	write(fd, &g_values.screen_height, 4);
	screenshot_norm_one(fd);
	screenshot_norm_two(fd, all_pix, zero, size);
	fill_screen(fd);
}
//void screenshot()
//{
//    if (g_values.should_save)
//    {
//        int a = 54;
//        int fd = open("screen.bmp", O_CREAT| O_RDWR, 0666);
//        write(fd, &a, 4);
//        close(fd);
//    }
//    g_values.should_save = 0;
//}