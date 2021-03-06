#include "../cub3d.h"

int count_sprites()
{
    int count = 0;

    for (int y = 0; y < g_values.matrix.matrixHeight; ++y)
        for (int x = 0; x < g_values.matrix.matrixWidth; ++x)
            count += (g_values.matrix.worldMap[y][x] == '2') ? 1 : 0;
    return (count);
}

void fill_sprites()
{
    int count = 0;

    for (int y = 0; y < g_values.matrix.matrixHeight; ++y)
    {
        for (int x = 0; x < g_values.matrix.matrixWidth; ++x)
        {
            if (g_values.matrix.worldMap[y][x] == '2')
            {
                g_values.sprites.sprites[count]->x = (double)y + 0.5;
                g_values.sprites.sprites[count]->y = (double)x + 0.5;
                g_values.sprites.sprites[count]->distance = 0;
                count++;
            }
        }
    }
}

void init_sprites()
{
    g_values.sprites.count = count_sprites();
    g_values.sprites.sprites = (t_sprite_elem **)malloc(g_values.sprites.count * (sizeof(t_sprite_elem*)));
    for (int i = 0; i < g_values.sprites.count; ++i)
        g_values.sprites.sprites[i] = (t_sprite_elem*)malloc(sizeof(t_sprite_elem));
    fill_sprites();
}

void bubble_sort()
{
    int i;
	int j;
    float tmp;

	i = 1;
	while (i < g_values.sprites.count)
	{
		j = i;
		while (j > 0 && (int)g_values.sprites.sprites[j]->distance > (int)g_values.sprites.sprites[j - 1]->distance)
		{
            tmp = g_values.sprites.sprites[j - 1]->distance;
            g_values.sprites.sprites[j - 1]->distance = g_values.sprites.sprites[j]->distance;
            g_values.sprites.sprites[j]->distance = tmp;
            tmp = g_values.sprites.sprites[j - 1]->x;
            g_values.sprites.sprites[j - 1]->x = g_values.sprites.sprites[j]->x;
            g_values.sprites.sprites[j]->x = tmp;
            tmp = g_values.sprites.sprites[j - 1]->y;
            g_values.sprites.sprites[j - 1]->y = g_values.sprites.sprites[j]->y;
            g_values.sprites.sprites[j]->y = tmp;
			--j;
		}
		++i;
	}
}

void			sort_sprites()
{
	int i;

	i = -1;
	while (++i < g_values.sprites.count)
	{
		g_values.sprites.sprites[i]->distance = ((g_values.currents.posX - g_values.sprites.sprites[i]->x)
		* (g_values.currents.posX - g_values.sprites.sprites[i]->x)
		+ (g_values.currents.posY - g_values.sprites.sprites[i]->y) * (g_values.currents.posY - g_values.sprites.sprites[i]->y));
	}
	if (g_values.sprites.count > 1)
		bubble_sort();
}