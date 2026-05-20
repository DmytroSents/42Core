#include "src/utils.h"
#include "mazegen/mazegen.h"


int main(int argc, char *argv[])
{
    t_param param = {
        .width = -1,    .exit  = {-1, -1},
        .height = -1,   .entry = {-1, -1},
        .perfect = false, .seed = 0,
        .output_file = NULL
    };

    int main_flag = txt_to_struct(argc, argv, &param);
    int cst_errno = error_check(&param, NULL);
    if (main_flag < 0 || cst_errno > 1) {
        ft_perror(cst_errno);
        if (param.output_file)
            free(param.output_file);
        return (-1);
    }

    /* VLA — must be declared before any branching that skips it */
    t_cell grid[param.width][param.height];
    grid_init(&param, grid);

    apply_42pattern(&param, grid);
    cst_errno = error_check(&param, grid);
    if (cst_errno > 1) {
        ft_perror(cst_errno);
        free(param.output_file);
        return (-1);
    }

    t_stack STACK = {0};
    STACK.capacity = param.width * param.height;
    STACK.path_t   = calloc(STACK.capacity, sizeof(t_way));
    if (!STACK.path_t) {
        free(param.output_file);
        return (printf("Out of mem!\n"), -1);
    }

    DFS_GEN(&STACK, &param, grid);
    reset_cell_type(&param, grid);

    char *path_str = BFS_PATH(&STACK, &param, grid);

    /* ncurses loop — regeneration happens inside here */
    run_interactive(&param, &STACK, grid, &path_str);

    /* write final state to file after user quits */
    maze_tofile(&param, grid, path_str);

    free(STACK.path_t);
    free(path_str);
    free(param.output_file);
    return (0);
}

void grid_init(t_param *p, t_cell (*grid)[p->height])
{
    for (int x = 0; x < p->width; x++)
    {
        for (int y = 0; y < p->height; y++)
        {
            grid[x][y].walls  = 15;
            grid[x][y].c_type = NOTHING;
            if (p->entry[0] == x && p->entry[1] == y)
                grid[x][y].c_type = ENTRY_X;
        }
    }
}