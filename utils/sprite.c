#include "../cub3d.h"

int count_sprites()
{
    int count = 0;

    for (int y = 0; y < g_values.matrix.matrixHeight; ++y)
    {
        for (int x = 0; x < g_values.matrix.matrixWidth; ++x)
        {
            g_values.sprites.sprites[count].x = (double)y + 0.5;
            g_values.sprites.sprites[count].y = (double)x + 0.5;
            g_values.sprites.sprites[count].distance = 0.0;
            count += (g_values.matrix.worldMap[y][x] == '2') ? 1 : 0;
        }
    }
    return (count);
}

void init_sprites()
{
    g_values.sprites.sprites = (t_sprite_elem *)malloc(g_values.sprites.count * (sizeof(t_sprite_elem) + 1));
    for (int i = 0; i < g_values.sprites.count; ++i)
        g_values.sprites.sprites[i] = *(t_sprite_elem*)malloc(sizeof(t_sprite_elem) + 1);
    g_values.sprites.count = count_sprites();
}

int find_greatest()
{
    double dist = 0.0;

    for (int i = 0; i < g_values.sprites.count; ++i)
    {
        if (dist < g_values.sprites.sprites[i].distance)
            dist = g_values.sprites.sprites[i].distance;
    }
    return (dist);
}

void reverse_sprites()
{
    t_sprite_elem *sprites = g_values.sprites.sprites;
    int count = g_values.sprites.count;

    for (int i = 0; i < g_values.sprites.count; ++i)
        g_values.sprites.sprites[i++] = sprites[--count];
}

void sort_sprites()
{
    t_sprite_elem temp_sprites;
    double last_dist = find_greatest();

    for (int i = g_values.sprites.count - 2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            if (g_values.sprites.sprites[j].distance > g_values.sprites.sprites[j+1].distance)
            {
                temp_sprites = g_values.sprites.sprites[j];
                g_values.sprites.sprites[j] = g_values.sprites.sprites[j+1];
                g_values.sprites.sprites[j+1] = temp_sprites;
            }
        }
    }
    reverse_sprites();
}
