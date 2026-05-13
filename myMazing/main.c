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
	int cst_errno = error_check(&param);
	if (main_flag < 0 || cst_errno > 1)
	{	ft_perror(cst_errno);
		if (param.output_file)
			free(param.output_file);
		return (-1);
	}
	if (cst_errno == 5)
		ft_perror(cst_errno);

		// grid of cells [x][y] size.
	t_cell grid[param.width][param.height];
	  // VLA grid on the stack: [width][height]
	grid_init(&param, grid);

	DFS_MAIN(&param, grid);

	render_maze(&param, grid);

	 //writes to output_file
	maze_tofile(&param, grid); 
 
	//print_struct(&param);

	//free(grid); --NotNow. Only for Heap-Based!
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
            grid[x][y].c_type = 0;
			// cell_type decision
			if (p->entry[0] == x && p->entry[1] == y)
				grid[x][y].c_type = 'E';
			else if (p->exit[0] == x && p->exit[1] == y)
				grid[x][y].c_type = -1;  // -'X'
        }
    }
}

