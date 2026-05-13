#include "mazegen.h"

int DFS_MAIN(t_param *p, t_cell grid[][p->height])
{
	srand(time(NULL));
	if (p->seed == 0)
		{	p->seed = rand();	}
	srand((unsigned int)p->seed);   // seed once

	uint16_t  x = (uint16_t)p->entry[0];
	uint16_t  y = (uint16_t)p->entry[1];

	apply_42pattern(p, grid);
	
	t_stack	STACK = {0}; //it's a stack of data about t_Way;

	STACK.capacity = p->width * p->height;
	STACK.p_tab = calloc(STACK.capacity, sizeof(t_way));
	if (!STACK.p_tab)
		return (printf("Out of mem!\n") , -1);

	push(&STACK, x, y); //_init_
	while (STACK.count > 0)
	{
			 // check unvisited only
		char direct = find_next(&STACK, p, grid);
	
		if (direct)	   // 'N' 'E' 'S' 'W'
			move_direct(direct, &STACK, p, grid);
		else
			pop(&STACK);
		//x = current->x;  y = current->y;
	}

	printf("amount:_%d\n", STACK.capacity);

	grid[p->exit[0]][p->exit[1]].c_type = 'X';
	if (p->perfect == FALSE)
		make_imperfect(p, grid);
	free(STACK.p_tab);
}

char find_next(t_stack *stk, t_param *p, t_cell grid[][p->height])
{
    int x = stk->p_tab[stk->count - 1].x;
    int y = stk->p_tab[stk->count - 1].y;
    char direction[4] = {0}; // set of directions
    uint8_t count = 0; 		// to shuffle them later

    if (x > 0)
    {
        if (grid[x - 1][y].c_type <= 0)
        {
            direction[count] = 'W';
            count++;
        }
    }
    if (x < p->width - 1)
    {
        if (grid[x + 1][y].c_type <= 0)
        {
            direction[count] = 'E';
            count++;
        }
    }
    if (y > 0)
    {
        if (grid[x][y - 1].c_type <= 0)
        {
            direction[count] = 'N';
            count++;
        }
    }
    if (y < p->height - 1)
    {
        if (grid[x][y + 1].c_type <= 0)
        {
            direction[count] = 'S';
            count++;
        }
    }
    if (count == 0)	// if nothing left
        return (0);						 // from set above
    return (direction[rand() % count]);	// move rand(direction)
}

void move_direct(char dirk, t_stack *stk, t_param *p, t_cell grid[][p->height])
{
	int  x = stk->p_tab[stk->count - 1].x ;
	int  y = stk->p_tab[stk->count - 1].y ;

	if (dirk == 'N') // go North
	{
		push(stk, x, y - 1);
		grid[x][y - 1].c_type = 'V';
		grid[x][y].walls = grid[x][y].walls & 14; //__1110
		grid[x][y - 1].walls = grid[x][y - 1].walls & 11; //__1011
	}
	else if (dirk == 'E') //go East
	{
		push(stk, x + 1, y);
		grid[x + 1][y].c_type = 'V';
		grid[x][y].walls = grid[x][y].walls & 13; //__1101
		grid[x + 1][y].walls = grid[x + 1][y].walls & 7; //__0111
	}
		
	else if (dirk == 'S') //go South
	{
		push(stk, x, y + 1);
		grid[x][y + 1].c_type = 'V';
		grid[x][y].walls = grid[x][y].walls & 11; //__1011
		grid[x][y + 1].walls = grid[x][y + 1].walls & 14; //__1110
	}
	else if (dirk == 'W') // go West
	{
		push(stk, x - 1, y);
		grid[x - 1][y].c_type = 'V';
		grid[x][y].walls = grid[x][y].walls & 7; //__0111
		grid[x - 1][y].walls = grid[x - 1][y].walls & 13; //__1101
	}		
}

void make_imperfect(t_param *p, t_cell grid[][p->height])
{
	int y = p->height ;
}