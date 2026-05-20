#include "mazegen.h"

static char move_backwards(char dir);
static void reconstruct_p(char *path_s, char *visit, t_param *p, t_cell grid[][p->height]);

char *BFS_PATH(t_stack *stack, t_param *p, t_cell grid[][p->height])
{
	uint8_t  w = 15;
	t_way	*curr = NULL;
	char	*visited = NULL;
	char	*path_str = NULL;

	path_str = calloc(stack->capacity, sizeof(char));
	if (!path_str)  return (NULL);

	visited = calloc(stack->capacity, sizeof(char));
	if (!visited)
	{	free(path_str);    return (NULL);	}

	stack->first = 0;
	stack->count = 0;

	push(stack, (uint16_t)p->entry[0], (uint16_t)p->entry[1]);
	grid[p->entry[0]][p->entry[1]].c_type = 3;

	while (stack->first < stack->count)
	{
		curr = &(stack->path_t[stack->first]); //current Cell
		w = grid[curr->x][curr->y].walls & 0xF; // it's Walls
		stack->first++;	 // qu.dequeue() - removes from start

		if (curr->x == (uint16_t)p->exit[0] && curr->y == (uint16_t)p->exit[1])
			break;

		if (curr->x > 0)
		{
			if (!(w & WALL_W) && grid[curr->x - 1][curr->y].c_type <= 0)
			{
				grid[curr->x - 1][curr->y].c_type = VISITED;
				push(stack, curr->x - 1, curr->y);
				visited[(curr->x - 1) + (curr->y * p->width)] = 'E';
			}
		}
		if (curr->x < p->width - 1)
		{
			if (!(w & WALL_E) && grid[curr->x + 1][curr->y].c_type <= 0)
			{
				grid[curr->x + 1][curr->y].c_type = VISITED;
				push(stack, curr->x + 1, curr->y);
				visited[(curr->x + 1) + (curr->y * p->width)] = 'W';
			}
		}
		if (curr->y > 0)
		{
			if (!(w & WALL_N) && grid[curr->x][curr->y - 1].c_type <= 0)
			{
				grid[curr->x][curr->y - 1].c_type = VISITED;
				push(stack, curr->x, curr->y - 1);
				visited[curr->x + ((curr->y - 1) * p->width)] = 'S';
			}
		}
		if (curr->y < p->height - 1)
		{
			if (!(w & WALL_S) && grid[curr->x][curr->y + 1].c_type <= 0)
			{
				grid[curr->x][curr->y + 1].c_type = VISITED;
				push(stack, curr->x, curr->y + 1);
				visited[curr->x + ((curr->y + 1) * p->width)] = 'N';
			}
		}
	}
	reconstruct_p(path_str, visited, p, grid);

	free(visited);
	rtsver_tf(path_str);
	return (path_str);
}

static void reconstruct_p(char *path_s, char *visit, t_param *p, t_cell grid[][p->height])
{
	int 	x = p->exit[0];
	int 	y = p->exit[1];
	char 	direct;
	size_t  i = 0;

	while (x != p->entry[0] || y != p->entry[1])
	{
		direct = visit[x + (y * p->width)];
		if (!direct) // sanity check
			break;
		path_s[i++] = move_backwards(direct);

		if (direct == 'E')       x++;
		else if (direct == 'W')  x--;
		else if (direct == 'N')  y--;
		else if (direct == 'S')  y++;
		grid[x][y].c_type = PATH_SHRT;
	}
	path_s[i] = 0;
}

static char move_backwards(char dir)
{
	if (dir == 'W')	 return 'E';
	if (dir == 'E')  return 'W';
	if (dir == 'S')  return 'N';
	if (dir == 'N')  return 'S';
	return 0;
}
