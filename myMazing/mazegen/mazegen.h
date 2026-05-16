#ifndef MAZEGEN_H
#define MAZEGEN_H

#include "../src/utils.h"
#include <stdlib.h>
#include <time.h>

#define IMPERFECT_RATE 42
//persentage, could be defined in config(don't wanna)

	// grid[↓x][y] (unfortunately it's upside down)
	//bin 0001 North == 1; ↑
	//bin 0010 East  == 2; →
	//bin 0100 South == 4; ↓
	//bin 1000 West  == 8; ←

enum Walls {
    WALL_N = 1 << 0,
    WALL_E = 1 << 1,
    WALL_S = 1 << 2,
    WALL_W = 1 << 3 
};

		// DFS — STACK, last in first out
int 	DFS_GEN(t_stack *stack, t_param *p, t_cell grid[][p->height]);

		// BFS — QUEUE, first in first out 
int 	BFS_PATH(t_stack *stack, t_param *p, t_cell grid[][p->height]);

void 	apply_42pattern(t_param *p, t_cell grid[][p->height]);

char 	find_next(t_stack *stk, t_param *p, t_cell grid[][p->height]);
void 	move_direct(char dirk, t_stack *stk, t_param *p, t_cell grid[][p->height]);

void    make_imperfect(t_stack *stk, t_param *p, t_cell grid[][p->height]);


void 	reset_cell_type(t_param *p, t_cell grid[][p->height]);

int  	pop(t_stack *stk);
void 	push(t_stack *stk, uint16_t new_x, uint16_t new_y);


#endif