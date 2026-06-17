#include "utils.h"

int	error_check(t_param *p, t_cell grid[][p->height])
{	//maze too small(non-crit)
	//output file check
	//Empty+Negative check;
	if (p->width <= 0 || p->height <= 0 ||
        p->exit[0] <= -1 || p->exit[1] <= -1 ||
		p->entry[0] <= -1 || p->entry[1] <= -1 )
		return 1;
	//Exit/Entry out of bounds
	if (p->entry[0] >= p->width || p->entry[1] >= p->height ||
        p->exit[0] >= p->width || p->exit[1] >= p->height )
        return 2;
	//Entry == Exit
	if (p->entry[0] == p->exit[0] && p->entry[1] == p->exit[1])
		return 3;
	if (!p->output_file || strlen(p->output_file) == 0)
		return 4;
	if (grid)
		if (grid[p->entry[0]][p->entry[1]].c_type == 2
		|| grid[p->exit[0]][p->exit[1]].c_type == 2)
		return 5;
	if (p->width < 7 || p->height < 5) return 0;
		
	return -1;
}

void	ft_perror(int num)
{
	const char *error_message[7] = {
    [0] = "",
    [1] = "ERROR: MissingKey/Negative int value.",
    [2] = "ERROR: Exit/Entry out of bounds.",
    [3] = "ERROR: Exit == Entry. (Must be different).", 
	[4] = "ERROR: Empty OUTPUT_FILE name.",
    [5] = "ERROR: Entry/Exit is on 42_pattern cell. ",
	//[6] = "Achtung: Maze too small for '42' patern;",
	};
	if (num)
		printf("%s\n", error_message[num]);
}

void print_struct(t_param *p)
{
	printf("%d\n%d\n", p->width, p->height);
	printf("%d,%d\n%d,%d\n", p->entry[0], p->entry[1], p->exit[0], p->exit[1]);
	printf("%s\n%d\n", p->output_file, p->seed); 
	if (p->perfect)
		printf("True\n");
	else if (!(p->perfect))
		printf("False\n");
}

char *strcasestr(const char *haystack, const char *needle)
{
    const char *h = haystack;
    
    while (*h) {
        const char *p = h;
        const char *n = needle;
        while (*p && *n && tolower((unsigned char)*p) == tolower((unsigned char)*n)) {
            p++; n++;
        }
        if (!*n) return (char *)h;  // Found!
        h++;
    }
    return NULL;
}
	//because atoi() is not enough
int	valid_intstr(char *str)
{
	
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\n' || *str == 0)
		return false;
	if (*str == '-' || *str == '+')
		str++;
	while (isdigit(*str))
		str++;
	if (*str == '\n' || *str == 0)
		return true;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\n' || *str == 0)
		return true;
	return false;	
}

int maze_tofile(t_param *p, t_cell grid[][p->height], char *path_str)
{
    if (!p || !p->output_file)
        return (-1);

    FILE *f = fopen(p->output_file, "w");
    if (!f)
        return (-1);

    // 1) Grid: row by row, one hex digit per cell
    for (int y = 0; y < p->height; y++)
    {
        for (int x = 0; x < p->width; x++)
        {
			unsigned char w = (unsigned char)grid[x][y].walls;
			// removes bits higher Decimal 15 
			w = w & 0xF;		//	[Hex F]
            fprintf(f, "%X", w);  //write to file
        }
        fputc('\n', f);
    }
    // 2) Entry and exit, then empty path line
    fprintf(f, "\n%d,%d\n", p->entry[0], p->entry[1]);
    fprintf(f, "%d,%d\n", p->exit[0],  p->exit[1]);
    
	fprintf(f, "\n"); 
	fprintf(f, "%s\n", path_str);

    fclose(f);
    return 0;
}

void	rtsver_tf(char *str)
{
	if (!str)	return ;

	size_t	len = strlen(str);
	size_t	half = len / 2;
	size_t	i;
	char	*buf = calloc(half + 1, sizeof(char));
	if (!buf)	return ;

	memcpy(buf, str, half);

	for (i = 0; i < half; i++)
		str[i] = str[len - 1 - i];

	for (i = 0; i < half; i++)
		str[len - half + i] = buf[half - 1 - i];

	str[len] = '\0';
	free(buf);
}
