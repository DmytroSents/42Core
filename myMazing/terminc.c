
#include "./src/utils.h"
#include "./mazegen/mazegen.h"

#define WALL_N 1
#define WALL_E 2
#define WALL_S 4
#define WALL_W 8

/*
** ANSI colors
*/

#define RESET	"\033[0m"
#define GREEN	"\033[32m"
#define RED		"\033[31m"
#define CYAN	"\033[36m"
#define YELLOW	"\033[33m"

// /*
// ** ==========================================================================
// ** Draw one maze row
// ** ==========================================================================
// */

// static void	draw_top_walls(t_param *p, t_cell grid[][p->height], int y)
// {
// 	int	x;

// 	for (x = 0; x < p->width; x++)
// 	{
// 		printf("+");

// 		if (grid[x][y].walls & WALL_N)
// 			printf("--");
// 		else
// 			printf("  ");
// 	}

// 	printf("+\n");
// }

// /*
// ** ==========================================================================
// ** Draw cell contents + vertical walls
// ** ==========================================================================
// */

// static void	draw_middle(t_param *p, t_cell grid[][p->height], int y)
// {
// 	int	x;

// 	for (x = 0; x < p->width; x++)
// 	{
// 		/*
// 		** Left wall
// 		*/
// 		if (grid[x][y].walls & WALL_W)
// 			printf("|");
// 		else
// 			printf(" ");

// 		/*
// 		** Cell content
// 		*/
// 		if (x == p->entry[0] && y == p->entry[1])
// 			printf(CYAN " E" RESET);

// 		else if (x == p->exit[0] && y == p->exit[1])
// 			printf(RED " X" RESET);

// 		else if (grid[x][y].c_type == 42)
// 			printf(YELLOW " #" RESET);

// 		else if (grid[x][y].walls == 15)
// 			printf("██");

// 		else
// 			printf("  ");
// 	}

// 	/*
// 	** Right border of last cell
// 	*/
// 	if (grid[p->width - 1][y].walls & WALL_E)
// 		printf("|");

// 	printf("\n");
// }

// /*
// ** ==========================================================================
// ** Draw bottom border
// ** ==========================================================================
// */

// static void	draw_bottom(t_param *p, t_cell grid[][p->height])
// {
// 	int	x;
// 	int	y;

// 	y = p->height - 1;

// 	for (x = 0; x < p->width; x++)
// 	{
// 		printf("+");

// 		if (grid[x][y].walls & WALL_S)
// 			printf("--");
// 		else
// 			printf("  ");
// 	}

// 	printf("+\n");
// }

// /*
// ** ==========================================================================
// ** Main render
// ** ==========================================================================
// */

// void	render_maze(t_param *p, t_cell grid[][p->height])
// {
// 	int	y;

// 	/*
// 	** IMPORTANT:
// 	**
// 	** render top -> bottom
// 	**
// 	** If you want mathematical coordinates:
// 	** for (y = p->height - 1; y >= 0; y--)
// 	*/

// 	for (y = 0; y < p->height; y++)
// 	{
// 		draw_top_walls(p, grid, y);
// 		draw_middle(p, grid, y);
// 	}

// 	draw_bottom(p, grid);
// }

static void draw_top_walls(t_param *p, t_cell grid[][p->height], int y)
{
    int x;

    for (x = 0; x < p->width; x++)
    {
        printf("+");
        if (grid[x][y].walls & WALL_N)
            printf("--");
        else
            printf("  ");
    }
    printf("+\n");
}

static void draw_middle(t_param *p, t_cell grid[][p->height], int y)
{
    int x;

    for (x = 0; x < p->width; x++)
    {
        if (grid[x][y].walls & WALL_W)
            printf("|");
        else
            printf(" ");

        if (x == p->entry[0] && y == p->entry[1])
            printf(CYAN " E" RESET);
        else if (x == p->exit[0] && y == p->exit[1])
            printf(RED " X" RESET);
        else if (grid[x][y].c_type == 42)
            printf(YELLOW " #" RESET);
        else if (grid[x][y].c_type == '*')
            printf(GREEN " ." RESET);
        else if (grid[x][y].walls == 15)
            printf("77");
        else
            printf("  ");
    }

    if (grid[p->width - 1][y].walls & WALL_E)
        printf("|");

    printf("\n");
}

static void draw_bottom(t_param *p, t_cell grid[][p->height])
{
    int x;
    int y = p->height - 1;

    for (x = 0; x < p->width; x++)
    {
        printf("+");
        if (grid[x][y].walls & WALL_S)
            printf("--");
        else
            printf("  ");
    }
    printf("+\n");
}

void render_maze(t_param *p, t_cell grid[][p->height])
{
    int y;

    for (y = 0; y < p->height; y++)
    {
        draw_top_walls(p, grid, y);
        draw_middle(p, grid, y);
    }
    draw_bottom(p, grid);
}