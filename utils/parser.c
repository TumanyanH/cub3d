# include "../cub3d.h"

int is_num (char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}
int is_space(char c)
{
    if(c == ' ' || c == '\n' || c == '\t'|| c == '\v'|| c == '\r'|| c == '\f')
        return (1);
    return (0);
}

char **count_height(int fd)
{
    int res = 0;
    char *line;
    int count = 1;
    int max_width = g_values.matrix.matrixWidth;
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
    //printf("W - %d, H - %d\n", max_width, count);
    g_values.matrix.matrixWidth = max_width;
    g_values.matrix.matrixHeight = count ;
    return (matrix);
}

int exists(const char *fname)
{
    int file;
    if ((file = open(fname, O_RDONLY, 0666)))
    {
        close(file);
        return 1;
    }
    return 0;
}

int is_empty(char *line)
{
    int i = 0;
    while (line[i] != '\0')
    {
        if (!is_space(line[i]))
            return (0);
    }
    return (1);
}

rgb createRGBA(int r, int g, int b, int a)
{   
    if (r < 256 && g < 256 && b < 256 && a < 256)
        return ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
    else
        error("Wrong RGBA value, every value should be less than 256");
}
int resolution(char *stop)
{
    char* num_str = malloc(ft_strlen(stop) * (sizeof(char) + 1));
    int i = 0;
    while (*stop != '\0' && ft_isdigit(*stop))
    {
        num_str[i++] = *stop;
        ++stop;
    }
    num_str[i] = '\0';
    g_values.screen_width = ft_atoi(num_str);
    if (*stop == ' ' && ft_isdigit(*(++stop)))
    {
        i = 0;
        while (*stop != '\0' && ft_isdigit(*stop))
            num_str[i++] = *(stop++);
    }
    num_str[i] = '\0';
    g_values.screen_height = ft_atoi(num_str);
    while (*stop != '\0')
    {
        if (is_space(*stop))
            ++stop;
        else
            error("Wrong resolution parameters");
    }
    return 1;
}

void texture(char **dest, char *stop)
{
    char *file_path;
    int i = 0;

    while (is_space(*stop))
        ++stop;
    file_path = malloc((ft_strlen(stop) + 1) * sizeof(char));
    while (stop[i] && !is_space(stop[i]))
    {
        file_path[i] = stop[i];
        // printf("%d - %c\n", i, temp[i]);
        ++i;
    }
    file_path[i] = '\0';
    if (file_path[ft_strlen(file_path) - 1] != 'm' || file_path[ft_strlen(file_path) - 2] != 'p' || file_path[ft_strlen(file_path) - 3] != 'x' || file_path[ft_strlen(file_path) - 4] != '.')
        error("Wrong texture file format!");
    if (!exists(file_path))
        error("Texture file for %s doesn't exist");
    *dest = file_path;
}

int my_rgb(char * line)
{
    int r = 0, g = 0, b = 0, a = 0, i = 0;
    while (is_space(line[i]))
        ++i;
    if (is_num(line[i]))
    {
        while (is_num(line[i]))
        {
            r = r * 10 + (line[i] - '0');
            ++i;
        }
        if (line[i] == ',')
        {
            ++i;
            if (is_num(line[i]))
            {
                while (is_num(line[i]))
                {
                    g = g * 10 + (line[i] - '0');
                    ++i;
                }
                if (line[i] == ',')
                {
                    ++i;
                    if (is_num(line[i]))
                    {
                        while (is_num(line[i]))
                        {
                            b = b * 10 + (line[i] - '0');
                            ++i;
                        }
                        while (line[i])
                        {
                            if(!is_space(line[i]))
                                error("Wrong rgb parameters #0");
                            ++i;
                        }
                    }
                    else 
                     error("Wrong rgb parameters #1"); 
                }
                else
                error("Wrong rgb parameters #2");              
            }
            else 
             error("Wrong rgb parameters #3");
        }
        else 
            error("Wrong rgb parameters #4");
    }
    else 
        error("Wrong rgb parameters #5");
    return (createRGBA(r, g, b, a));
}


int parse_opts(char *line)
{
    int ret;
    char *stop;
    int i = 0;

    int screenX = 0, screenY = 0;
    mlx_get_screen_size(g_values.mlx_ptr, &screenX, &screenY);
    while (is_space(line[i]) && line[i] != '\0')
        ++i;
    if (line[i] == 'R' && *(stop = (ft_strchr(line, 'R') + 1)) == ' ' && g_values.parser_flags.res == 0)
    {
        ++stop;
        resolution(stop);
        g_values.parser_flags.res = 1;
    } 
    else if (line[i] == 'N' && line[i + 1] == 'O' && *(stop = (ft_strchr(line, 'N') + 2)) == ' ' && g_values.parser_flags.tex_n == 0) 
    {
        ++stop;
        texture(&g_values.p.nor_tex, stop);
        g_values.parser_flags.tex_n = 1;
    }
    else if (line[i] == 'S' && line[i + 1] == 'O' && *(stop = (ft_strchr(line, 'S') + 2)) == ' ' && g_values.parser_flags.tex_s == 0)
    {
        ++stop;
        texture(&g_values.p.sou_tex, stop);
        g_values.parser_flags.tex_s = 1;
    }
    else if (line[i] == 'E' && line[i + 1] == 'A' && *(stop = (ft_strchr(line, 'E') + 2)) == ' ' && g_values.parser_flags.tex_e == 0)
    {
        ++stop;
        texture(&g_values.p.eas_tex, stop);
        g_values.parser_flags.tex_e = 1;
    }
    else if (line[i] == 'W' && line[i + 1] == 'E' && *(stop = (ft_strchr(line, 'W') + 2)) == ' ' && g_values.parser_flags.tex_w == 0) 
    {
        ++stop;
        texture(&g_values.p.wes_tex, stop);
        g_values.parser_flags.tex_w = 1;
    }
    else if (line[i] == 'S' && *(stop = (ft_strchr(line, 'S') + 1)) == ' ' && g_values.parser_flags.spr == 0)
    {
        ++stop;
        texture(&g_values.p.spr_tex, stop);
        g_values.parser_flags.spr = 1;
    }
    else if (line[i] == 'F' && *(stop = (ft_strchr(line, 'F') + 1)) == ' ' && g_values.parser_flags.floor == 0)
    {
        ++stop;
        g_values.p.floore_color = my_rgb(stop);
        g_values.parser_flags.floor = 1;
    }
    else if (line[i] == 'C' && *(stop = (ft_strchr(line, 'C') + 1)) == ' ' && g_values.parser_flags.ceiling == 0)
    {
        ++stop;
        g_values.p.ceilling_color = my_rgb(stop);
        g_values.parser_flags.ceiling = 1;
    }
    else if (is_space(line[i]) || line[i] == '\0')
        ++stop;
    else 
        error("wrong parameter");
    g_values.screen_width = (g_values.screen_width < screenX) ? g_values.screen_width : screenX;
    g_values.screen_height = (g_values.screen_height < screenY) ? g_values.screen_height : screenY;
    return 1;
}

int check_parser_flags()
{
    return (g_values.parser_flags.res 
            && g_values.parser_flags.tex_e
            && g_values.parser_flags.tex_w
            && g_values.parser_flags.tex_s
            && g_values.parser_flags.tex_n
            && g_values.parser_flags.spr
            && g_values.parser_flags.ceiling
            && g_values.parser_flags.floor);
}


void matrix_parser(char *filepath)
{
    char *line = NULL;
    int res = 0;
    int fd = open(filepath, O_RDWR|O_CREAT, 0666);
    char **worldMatrix;
    int i = 0, j = 0;
    while ((res = get_next_line(fd, &line)) && check_parser_flags() != 1)
        parse_opts(line);
    while (1)
    {  
        if ((res = get_next_line(fd, &line)) && !is_empty (line))
        {
            g_values.matrix.matrixWidth = ft_strlen(line); 
            break;
        }    
    }
    worldMatrix = count_height(fd);
    close(fd);
    fd = open(filepath, O_RDWR|O_CREAT, 0666);
    while ((res = get_next_line(fd, &line)) > 0 )
    {    
        if(ft_strchr(line, 'R') || ft_strchr(line, 'W') || ft_strchr(line, 'A') || ft_strchr(line, 'E') || ft_strchr(line, 'S') 
        || ft_strchr(line, 'O') || ft_strchr(line, 'N') || ft_strchr(line, 'F') || is_empty(line) || ft_strchr(line, 'C'))
            continue;
        else
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
                    else if (line[j] == '0' || line[j] == '1' || line[j] == '2' || line[j] == '3' || line[j] == '4' || line[j] == '5')
                        worldMatrix[i][j] = line[j];
                    else if (line[j] == ' ')
                        worldMatrix[i][j] = '*';
                }
                ++j;
            }
            while (j < g_values.matrix.matrixWidth)
            {
                worldMatrix[i][j] = '*';
                ++j;
            }
            worldMatrix[i][j] = '\0';
            ++i;
        }
    }
    g_values.matrix.worldMap = worldMatrix;
    for (int k = 0; k < i; ++k)
    {
        //printf("line number %d ", k + 1);
        for(int l = 0; l < j; ++l)
        {
            printf("%c", g_values.matrix.worldMap[k][l]);
        }
        printf("\n");
    }
    matrix_checker();
}


int matrix_checker()
{
    char **vm = g_values.matrix.worldMap;
    for (int i = 0; i < g_values.matrix.matrixHeight; ++i)
    {
        for(int j = 0; j < g_values.matrix.matrixWidth; ++j)
        {
            //printf("%c - %d, %d\n",vm[i][j], i, j);
            if (vm[0][j] != '1' && vm[0][j] != '*' && vm[g_values.matrix.matrixHeight - 1][j] != '1' && vm[g_values.matrix.matrixHeight - 1][j] != '*' && 
             vm[i][0] != '1' && vm[i][0] != '*' && vm[i][g_values.matrix.matrixWidth - 1] != '1' && vm[i][g_values.matrix.matrixWidth - 1] != '*')
            {
                printf("Error\n");
                exit(0);
            }
        }
        //printf("\n");
    }
    
    for (int i = 1; i < g_values.matrix.matrixHeight - g_values.matrix.rows_count - 2; ++i)
    {
        for (int j = 1; j < g_values.matrix.matrixWidth - 1; ++j)
        {
            //printf("vm[%d][%d] - %c\n", i, j, vm[i][j]);
            if (vm[i][j] == '*')
            {
                if ((vm[i][j + 1] != '1' && vm[i][j + 1] != '*') || (vm[i + 1][j] != '1' && vm[i + 1][j] != '*'))              
                {
                    printf("Error mapy patov chi shrjapakvac\n");
                    exit(0);
                }

            }
            else if (vm[i][j] > '9' || vm[i][j] < '0')
            {
                // printf("%d\n\n", g_values.matrix.matrixHeight - 1);
                printf("Error urish simvol\n");
                exit(0);
            }
            else
            {
                // printf("The element of matrix [%d][%d]: %c\n",i, j, vm[i][j]);
            }
        }
    }
    printf("Chisht matrix\n");
    return 0;
}
