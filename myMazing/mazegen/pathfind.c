#include "mazegen.h"

char *BFS_PATH(t_stack *stack, t_param *p, t_cell grid[][p->height])
{
    uint16_t x = (uint16_t)p->entry[0];
    uint16_t y = (uint16_t)p->entry[1];
    uint8_t w;
    int found = 0;

    char (*came_from)[p->height] = calloc(p->width, sizeof(*came_from));
    if (!came_from)
        return NULL;

    stack->first = 0;
    stack->count = 0;
    push(stack, x, y);
    grid[x][y].c_type = VISITED;

    while (stack->first < stack->count)
    {
        x = stack->path_t[stack->first].x;
        y = stack->path_t[stack->first].y;
        stack->first++;

        if (x == (uint16_t)p->exit[0] && y == (uint16_t)p->exit[1])
        {
            found = 1;
            break;
        }

        w = grid[x][y].walls & 0xF;

        if (!(w & WALL_N) && y > 0 && grid[x][y - 1].c_type == NOTHING)
        {
            grid[x][y - 1].c_type = VISITED;
            came_from[x][y - 1] = 'N';
            push(stack, x, y - 1);
        }
        if (!(w & WALL_E) && x + 1 < p->width && grid[x + 1][y].c_type == NOTHING)
        {
            grid[x + 1][y].c_type = VISITED;
            came_from[x + 1][y] = 'E';
            push(stack, x + 1, y);
        }
        if (!(w & WALL_S) && y + 1 < p->height && grid[x][y + 1].c_type == NOTHING)
        {
            grid[x][y + 1].c_type = VISITED;
            came_from[x][y + 1] = 'S';
            push(stack, x, y + 1);
        }
        if (!(w & WALL_W) && x > 0 && grid[x - 1][y].c_type == NOTHING)
        {
            grid[x - 1][y].c_type = VISITED;
            came_from[x - 1][y] = 'W';
            push(stack, x - 1, y);
        }
    }

    if (!found)
    {
        free(came_from);
        return NULL;
    }

    char *result = reconstruct(p, came_from, grid);
    free(came_from);
    return result;
}

char *reconstruct(t_param *p, char came_from[][p->height], t_cell grid[][p->height])
{
    int sx = p->entry[0];
    int sy = p->entry[1];
    int tx = p->exit[0];
    int ty = p->exit[1];
    int len = 0;

    while (tx != sx || ty != sy)
    {
        char d = came_from[tx][ty];
        if (!d)
            return NULL;
        len++;
        if (d == 'N') ty++;
        else if (d == 'S') ty--;
        else if (d == 'E') tx--;
        else if (d == 'W') tx++;
    }

    char *path_str = calloc(len + 1, sizeof(char));
    if (!path_str)
        return NULL;

    tx = p->exit[0];
    ty = p->exit[1];
    int pos = len;

    while (tx != sx || ty != sy)
    {
        char d = came_from[tx][ty];
        path_str[--pos] = d;
        grid[tx][ty].c_type = PATH_SHRT;
        if (d == 'N') ty++;
        else if (d == 'S') ty--;
        else if (d == 'E') tx--;
        else if (d == 'W') tx++;
    }

    grid[sx][sy].c_type = ENTRY_X;
    return path_str;
}
