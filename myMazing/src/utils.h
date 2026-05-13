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

typedef struct params
{
    int		width;
    int		height;
    int		exit[2];
	int		entry[2];
	bool	perfect;
	int		seed;
	char	*output_file;
}		t_param;

typedef struct cell
{
	uint8_t		walls;
	char		c_type;
	//bool		visited;
}		t_cell;

void	ft_perror(int num);
int		error_check(t_param *p);
void	print_struct(t_param *p);

int 	txt_to_struct(int argc, char *argv[], t_param *p);

int		process_line(t_param *params, char *buffer);
int		process_int(t_param *p, char *key_s, char flag_c);
int		process_str(t_param *p, char *key_s, char flag_c);
int		valid_intstr(char *str);
char	*strcasestr(const char *haystack, const char *needle);

int 	maze_tofile(t_param *p, t_cell grid[][p->height]);

//for Human version of visuals For MLX
static inline int inv_y(t_param *p, int y)
		{	return (p->height - 1 - y);	 }



#endif