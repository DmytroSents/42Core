#ifndef MAZEGEN_H
#define MAZEGEN_H

#include "../src/utils.h"
#include <stdlib.h>
#include <time.h>

typedef struct new_way
{
	uint16_t 	x;
	uint16_t	y;
	//uint8_t cases;
}	t_way;

typedef struct stack
{
	size_t	 count;
	t_way *p_tab;
	size_t capacity;
}	t_stack;

	// grid[↓x][y] (unfortunately it's upside down)
	//bin 0001 North == 1; ↑
	//bin 0010 East  == 2; →
	//bin 0100 South == 4; ↓
	//bin 1000 West  == 8; ←


int  	DFS_MAIN(t_param *p, t_cell grid[][p->height]);
void 	apply_42pattern(t_param *p, t_cell grid[][p->height]);

void 	make_imperfect(t_param *p, t_cell grid[][p->height]);

char 	find_next(t_stack *stk, t_param *p, t_cell grid[][p->height]);
void 	move_direct(char dirk, t_stack *stk, t_param *p, t_cell grid[][p->height]);

int  	pop(t_stack *stk);
void 	push(t_stack *stk, uint16_t new_x, uint16_t new_y);


#endif