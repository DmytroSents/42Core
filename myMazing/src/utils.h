#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 512
#endif

#define TRUE 1
#define FALSE 0

typedef struct  {
    int		width;
    int		height;
    int		exit[2];
	int		entry[2];
	bool	perfect;
	int		seed;
	char	*output_file;
}	t_param;

typedef struct {
	uint8_t	   walls; // unsigned int 8 bit 00000000
	uint8_t	   c_type; //coz <bool> is not enough
}	t_cell;

enum c_Types {
    NOTHING = 0,
    ENTRY_X = 1,
    PATTERN = 2,
    VISITED = 3,
	PATH_SHRT = 4, 
};


//(re)used for both: generation and pathfinding;
typedef struct  {
	uint16_t 	x;
	uint16_t	y;
	char 	    direct; //for Path
}	t_way;
	
//not Dynamik but Array!
typedef struct  {
	size_t 	 first; //for queue.pop()
	size_t	 count;
	t_way  *path_t; // ->t_way{x,y}
	size_t capacity;
}	t_stack; //same struct for both algo


void	ft_perror(int num);

void	print_struct(t_param *p);
int		error_check(t_param *p, t_cell grid[][p->height]);

int 	txt_to_struct(int argc, char *argv[], t_param *p);

int		process_line(t_param *params, char *buffer);
int		process_int(t_param *p, char *key_s, char flag_c);
int		process_str(t_param *p, char *key_s, char flag_c);
int		valid_intstr(char *str);
char	*strcasestr(const char *haystack, const char *needle);

int 	maze_tofile(t_param *p, t_cell grid[][p->height], char *str);


//for Human version of visuals in MLX
static inline int inv_y( t_param *p, int y)
/*Not implemented yet*/{ return (p->height - 1 - y);	 }

#endif