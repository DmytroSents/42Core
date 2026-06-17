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
	char *path_str = NULL;

	if (txt_to_struct(argc, argv, &param) < 0)
		return (127);
	
    int cst_errno = error_check(&param, NULL);
    if (cst_errno < 0) {
        ft_perror(cst_errno);
        if (param.output_file) free(param.output_file);
        	return (-1);
    }

    /* VLA — must be declared before any branching that skips it */
    t_cell grid[param.width][param.height];
    grid_init(&param, grid);

    apply_42pattern(&param, grid);
    cst_errno = error_check(&param, grid);
    if (cst_errno) {
        ft_perror(cst_errno);
        if (param.output_file) free(param.output_file);
		if (cst_errno != 6)
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

    path_str = BFS_PATH(&STACK, &param, grid);

    /* ncurses loop — regeneration happens inside here */
    run_interactive(&param, &STACK, grid, &path_str);

	// render_maze(p, grid); --just in case.

    /* write final state to file after user quits */
    maze_tofile(&param, grid, path_str);

	if (STACK.path_t)
    	free(STACK.path_t);
    if (path_str)
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
