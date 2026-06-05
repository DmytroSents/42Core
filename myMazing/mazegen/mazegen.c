#include "mazegen.h"

int DFS_GEN(t_stack *stack, t_param *p, t_cell grid[][p->height])
{
	int 	new_seed;

	if (p->seed == 0)
		{	new_seed = (int)time(NULL);	}
	if (p->seed != 0)
		{	new_seed = p->seed;	}
	srand((unsigned int)new_seed);   // seed once
	

	uint16_t  x = (uint16_t)p->entry[0];
	uint16_t  y = (uint16_t)p->entry[1];

	push(stack, x, y); //_init_
	while (stack->count > 0)
	{
			// check unvisited only
		char direct = find_next(stack, p, grid);
	
		if (direct)	   // 'N' 'E' 'S' 'W'
			move_direct(direct, stack, p, grid);
		else
			pop_last(stack);
		//x = current->x;  y = current->y;
	}
	
	if (p->perfect == FALSE)
		make_imperfect(stack, p, grid); 

	return (0);
}

void make_imperfect(t_stack *stk, t_param *p, t_cell grid[][p->height])
{	
	uint32_t	rand_count = 0;
	uint8_t 	open_walls = 0;
	uint8_t		current_w = 0;

	stk->count = 0;

	//[тупик] DeadEnd has only one open WALL;
	for (int y = 1; y < p->height - 1; y++)
	{
		for (int x = 1; x < p->width - 1; x++)
		{
			if (grid[x][y].c_type == FT_CELL)
				continue ;
			current_w = grid[x][y].walls & 0xF;
			open_walls = !(current_w & WALL_N) + !(current_w & WALL_E)
					   + !(current_w & WALL_S) + !(current_w & WALL_W);
			if (open_walls == 1)
                push(stk, x, y);
		}
	}

	//rand_count = stk->count - 1; == 99%
	rand_count = ((stk->count - 1) * IMPERFECT_RATE) / 100;
	if (rand_count == 0)
		return ;

	for (uint32_t i = 0; i < rand_count; i++)
    {
        int 	 pick = rand() % stk->count;
        uint16_t x = stk->path_t[pick].x;
        uint16_t y = stk->path_t[pick].y;

        current_w = grid[x][y].walls & 0xF;

	// find which wall is open (the one clear bit)
	if (!(current_w & WALL_N))  // open side is North → break South
	{
		if (y < p->height - 1 && grid[x][y + 1].c_type != FT_CELL)
		{ grid[x][y].walls &= ~WALL_S; grid[x][y + 1].walls &= ~WALL_N; }
	}
	else if (!(current_w & WALL_E))  // open side is East → break West
	{
		if (x > 0 && grid[x - 1][y].c_type != FT_CELL)
		{ grid[x][y].walls &= ~WALL_W; grid[x-1][y].walls &= ~WALL_E; }
	}
	else if (!(current_w & WALL_S))  // open side is South → break North
	{
		if (y > 0 && grid[x][y - 1].c_type != FT_CELL)
		{ grid[x][y].walls &= ~WALL_N; grid[x][y - 1].walls &= ~WALL_S; }
	}
	else if (!(current_w & WALL_W))  // open side is West → break East
	{
		if (x < p->width - 1 && grid[x + 1][y].c_type != FT_CELL)
		{ grid[x][y].walls &= ~WALL_E; grid[x + 1][y].walls &= ~WALL_W; }
	}

        // remove from list: swap with last
        stk->path_t[pick] = stk->path_t[stk->count - 1];
        stk->count--;
    }
}
