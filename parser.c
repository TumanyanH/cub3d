# include "cub3d.h"

char **count_height(int fd)
{
    int res = 0;
    char *line;
    int count = 0;
    int max_width = 0;
    char **matrix;

    while ((res = get_next_line(fd, &line)) > 0)
    {
        if (max_width < ft_strlen(line))
            max_width = ft_strlen(line);
        count++;
    }
    matrix = (char **)malloc(sizeof(char *) * (count + 1));
    res = 0;
    while (res < count)
        matrix[res++] = (char *)malloc(sizeof(char) * (max_width + 1));
    matrix[res] = NULL;
    g_values.matrix.matrixWidth = max_width;
    g_values.matrix.matrixHeight = count;
    return (matrix);
}

void matrix_parser(char *filepath)
{
    char *line = NULL;
    int res = 0;
    int fd = open(filepath, O_RDWR|O_CREAT, 0666);
    char **worldMatrix;
    int i = 0, j = 0;
    worldMatrix = count_height(fd);
    close(fd);
    fd = open(filepath, O_RDWR|O_CREAT, 0666);
    while ((res = get_next_line(fd, &line)) > 0)
    {
        j = 0;
        while (line[j] != '\0')
        {
            if (line[j] != '\n')
            {
                if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E' || line[j] == 'W')
                {
                    worldMatrix[i][j] = '0';
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
                else /*if (line[j] == '0' || line[j] == '1' || line[j] == '2' || line[j] == '3' || line[j] == '4')*/
                    worldMatrix[i][j] = line[j];
                // else if ((line[j] > '5' && line[j] <= '9') || line[j] == ' ')
                //     worldMatrix[i][j] = ' ';
            }
            ++j;
        }
        while (j < g_values.matrix.matrixWidth)
        {
            worldMatrix[i][j] = ' ';
            ++j;
        }
        worldMatrix[i][j] = '\0';
        ++i;
    }
    g_values.matrix.worldMap = worldMatrix;
    for (int k = 0; k < i; ++k)
    {
        for(int l = 0; l < j; ++l)
        {
            printf("%c", g_values.matrix.worldMap[k][l]);
        }
        printf("\n");
    }
    // matrix_checker();
}

int is_space(char c)
{
    if(c == ' ' || c == '\n' || c == '\t'|| c == '\v'|| c == '\r'|| c == '\f')
        return (1);
    return (0);
}

int matrix_checker()
{
    char **vm = g_values.matrix.worldMap;
    int k = 0;
    //piti yst maxwidthi matrixy lcvi ete toxi erkarutyuny poqra max widthic mnacacy dni probel
    printf("%d\n\n", g_values.matrix.matrixWidth);
    for (int i = 0; i < g_values.matrix.matrixHeight; i++)
    {
        for(int j = 0; j < g_values.matrix.matrixWidth; j++)
        {
            if(vm[0][j] != '1' || vm[i][0] != '1' || vm[g_values.matrix.matrixHeight - 1][0] != '1' || vm[0][g_values.matrix.matrixWidth - 1] != '1' || vm[0][j] != ' ' || vm[i][0] != ' ' || vm[g_values.matrix.matrixHeight - 1][0] != ' ' || vm[0][g_values.matrix.matrixWidth - 1] != ' ')
            {
                ++k;
                printf("Error number %d\n", k);
                exit(0);
            }
        }
    }


    return 0;
}
