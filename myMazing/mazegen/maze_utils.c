#include "mazegen.h"

void apply_42pattern(t_param *p, t_cell grid[][p->height])
{
	int start_x = (p->width - 7) / 2;
	int start_y = (p->height - 5) / 2;

	static const uint8_t ft_42[5][7] = {
		{1, 0, 0, 0, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 1},
		{0, 0, 1, 0, 1, 0, 0},
		{0, 0, 1, 0, 1, 1, 1}		};
	if (5 > p->height || 7 > p->width)
	{
		printf("Maze is too small to add '42' logo;\n");
		return ;
	}

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 7; x++)
		{
		if (ft_42[y][x] == 1)
			{
			grid[start_x + x][start_y + y].walls = 15;
			 //my custom flag have been set here
			grid[start_x + x][start_y + y].c_type = 42;
			}
		}
	}
}

void push(t_stack *stk, uint16_t new_x, uint16_t new_y)
{
	stk->p_tab[stk->count].x = new_x;
	stk->p_tab[stk->count].y = new_y;
	stk->count++;
	//stk->p_tab[stk->count++] = (t_way){new_x, new_y}; --Inline syntax!
}

int pop(t_stack *stk)
{
	if (stk->count <=0)
		return (-1);
	stk->count--;
	stk->p_tab[stk->count].x = 0;
	stk->p_tab[stk->count].y = 0;
	return (0);
}
