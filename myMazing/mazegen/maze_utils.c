#include "mazegen.h"

void apply_42pattern(t_param *p, t_cell grid[][p->height])
{
	if (p->height < 5 || p->width < 7)
	{
		printf("Maze is too small to add '42' logo;\n");
		return ;
	}

	int start_x = (p->width - 7) / 2;
	int start_y = (p->height - 5) / 2;

	static const uint8_t ft_42[5][7] = {
		{1, 0, 0, 0, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 1},
		{0, 0, 1, 0, 1, 0, 0},
		{0, 0, 1, 0, 1, 1, 1}
	};

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			if (ft_42[y][x] == 1)
			{
				int gx = start_x + x;
				int gy = start_y + y;
				grid[gx][gy].walls  = 15;  // all walls closed
				grid[gx][gy].c_type = 2;   // pattern sentinel
			}
		}
	}

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			if (ft_42[y][x] == 1)
			{
				int gx = start_x + x;
				int gy = start_y + y;

				// North neighbor → force its South wall closed
				if (gy > 0 && grid[gx][gy - 1].c_type != 2)
					grid[gx][gy - 1].walls |= WALL_S;

				// South neighbor → force its North wall closed
				if (gy < p->height - 1 && grid[gx][gy + 1].c_type != 2)
					grid[gx][gy + 1].walls |= WALL_N;

				// West neighbor → force its East wall closed
				if (gx > 0 && grid[gx - 1][gy].c_type != 2)
					grid[gx - 1][gy].walls |= WALL_E;

				// East neighbor → force its West wall closed
				if (gx < p->width - 1 && grid[gx + 1][gy].c_type != 2)
					grid[gx + 1][gy].walls |= WALL_W;
			}
		}
	}
	error_check(p, grid);
}

void push(t_stack *stk, uint16_t new_x, uint16_t new_y)
{
	stk->path_t[stk->count].x = new_x;
	stk->path_t[stk->count].y = new_y;
	stk->count++;
	//stk->path_t[stk->count++] = (t_way){new_x, new_y}; --Inline syntax!
}

int pop_last(t_stack *stk)
{
	if (stk->count <= 0)
		return (-1);
	stk->count--;
	return (0);
}

int dequeue(t_stack *stk)
{
	if (stk->count <= 0 || stk->first == stk->count)
		return (-1);
	stk->first++;
	return (stk->first);
}

char find_next(t_stack *stk, t_param *p, t_cell grid[][p->height])
{
    int x = stk->path_t[stk->count - 1].x;
    int y = stk->path_t[stk->count - 1].y;
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
	int  x = stk->path_t[stk->count - 1].x ;
	int  y = stk->path_t[stk->count - 1].y ;

	if (dirk == 'N') // go North
	{
		push(stk, x, y - 1);
		grid[x][y - 1].c_type = 3;	       		// ~ Bitwise NOT
		grid[x][y].walls = grid[x][y].walls & ~WALL_N; //__1110
		grid[x][y - 1].walls = grid[x][y - 1].walls & ~WALL_S; //__1011
	}
	else if (dirk == 'E') //go East
	{
		push(stk, x + 1, y);
		grid[x + 1][y].c_type = 3;
		grid[x][y].walls = grid[x][y].walls & ~WALL_E; //__1101
		grid[x + 1][y].walls = grid[x + 1][y].walls & ~WALL_W; //__0111
	}
	else if (dirk == 'S') //go South
	{
		push(stk, x, y + 1);
		grid[x][y + 1].c_type = 3;
		grid[x][y].walls = grid[x][y].walls & ~WALL_S; //__1011
		grid[x][y + 1].walls = grid[x][y + 1].walls & ~WALL_N; //__1110
	}
	else if (dirk == 'W') // go West
	{
		push(stk, x - 1, y);
		grid[x - 1][y].c_type = 3;
		grid[x][y].walls = grid[x][y].walls & ~WALL_W; //__0111
		grid[x - 1][y].walls = grid[x - 1][y].walls & ~WALL_E; //__1101
	}		
}

void reset_cell_type(t_param *p, t_cell grid[][p->height])
{
    for (int x = 0; x < p->width; x++)
        for (int y = 0; y < p->height; y++)
            if (grid[x][y].c_type == VISITED
                || grid[x][y].c_type == ENTRY_X)  // ← add this
                grid[x][y].c_type = NOTHING;
    // re-mark entry so BFS seed check works
    grid[p->entry[0]][p->entry[1]].c_type = ENTRY_X;
}
