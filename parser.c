# include "cub3d.h"

int **count_height(int fd)
{
    int res = 0;
    char *line;
    int count = 0;
    int max_width = 0;
    int **matrix;

    while ((res = get_next_line(fd, &line)) > 0)
    {
        if (max_width < ft_strlen(line))
            max_width = ft_strlen(line);
        count++;
    }
    matrix = (int **)malloc(sizeof(int *) * (count + 1));
    res = 0;
    while (res < count)
        matrix[res++] = (int *)malloc(sizeof(int) * (max_width + 1));
    matrix[res] = NULL;
    return (matrix);
}

void matrix_parser(char *filepath)
{
    char *line = NULL;
    int res = 0;
    int fd = open(filepath, O_RDWR|O_CREAT, 0666);
    int **worldMatrix;
    int i = 0, j = 0;
    worldMatrix = count_height(fd);
    close(fd);
    fd = open(filepath, O_RDWR|O_CREAT, 0666);
    while ((res = get_next_line(fd, &line)) > 0)
    {
        j = 0;
        while (line[j] != '\0')
        {
            if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E' || line[j] == 'W')
            {
                worldMatrix[i][j] = 0;
                g_values.currents.posX = j;
                g_values.currents.posY = i;
                switch (line[j])
                {
                case 'N':
                    g_values.currents.dirX = 0;
                    g_values.currents.dirY = 1;
                    break;
                case 'S':
                    g_values.currents.dirX = 0;
                    g_values.currents.dirY = -1;
                    break;
                case 'E':
                    g_values.currents.dirX = 1;
                    g_values.currents.dirY = 0;
                    break;
                case 'W':
                    g_values.currents.dirX = -1;
                    g_values.currents.dirY = 0;
                    break;
                default:
                    g_values.currents.dirX = 0;
                    g_values.currents.dirY = 0;
                    break;
                }
            }
            else if (line[j] == '0' || line[j] == '1' || line[j] == '2' || line[j] == '3' || line[j] == '4')
                worldMatrix[i][j] = line[j] - '0';
            else if ((line[j] >= '5' && line[j] <= '9') || line[j] == ' ')
                worldMatrix[i][j] = 0;
            j++;
        }
        worldMatrix[i][j] = NULL;
        i++;
    }
    g_values.worldMap = worldMatrix;
}