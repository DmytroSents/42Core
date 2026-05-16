#include "src/utils.h"
#include "mazegen/mazegen.h"

static void grid_init(t_param *p, t_cell (*grid)[p->height]);

	// reqq refactoring
void	render_maze(t_param *p, t_cell grid[][p->height]);

int main(int argc, char *argv[])
{		//_init_ empty
	t_param param = {
	.width = -1,	.exit = {-1, -1},
	.height = -1,	.entry = {-1, -1},
	.perfect = false,	.seed = 0,
	.output_file = NULL
	};
		//parse and fill parameters
	int main_flag = txt_to_struct(argc, argv, &param);
	int cst_errno = error_check(&param, NULL);
	if (main_flag < 0 || cst_errno > 1) {
		ft_perror(cst_errno);
		if (param.output_file)
			free(param.output_file);
		return (-1);	}

		
	//VLA grid on the stack: [width][height]
	t_cell grid[param.width][param.height];
	grid_init(&param, grid);
	
	apply_42pattern(&param, grid);
	//run again to check error N 5
	cst_errno = error_check(&param, grid);
	if (cst_errno > 1) {
		ft_perror(cst_errno);
		if (param.output_file)
			free(param.output_file);
		return (-1);	}
	 
	t_stack	STACK = {0}; //it's a stack with Path;

	STACK.capacity = param.width * param.height;
	STACK.path_t = calloc(STACK.capacity, sizeof(t_way));
	if (!STACK.path_t)
		return (printf("Out of mem!\n"), -1);

	DFS_GEN(&STACK, &param, grid);
	reset_cell_type(&param, grid);
	char *path_str = BFS_PATH(&STACK, &param, grid);

	render_maze(&param, grid);
	 //writes to output_file
	maze_tofile(&param, grid, path_str); 
	
	//printf("%d\n", param.seed);
	//print_struct(&param);

	if (STACK.path_t)
		free(STACK.path_t);
	if (path_str)
		free(path_str);
	
	//free(grid); --NotNow. Only for Heap-Based
	free(param.output_file);
	return (0);
}

static void grid_init(t_param *p, t_cell (*grid)[p->height])
{
	for (int x = 0; x < p->width; x++)
	{
        for (int y = 0; y < p->height; y++)
		{	
            grid[x][y].walls  = 15; //_00001111 bin
            grid[x][y].c_type = NOTHING;
			// cell_type decision
			if (p->entry[0] == x && p->entry[1] == y)
				grid[x][y].c_type = ENTRY_X;
			else if (p->exit[0] == x && p->exit[1] == y)
				grid[x][y].c_type = NOTHING; //not used for generation. 
        }
    }
}

