
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	size_t	i = 0;
	int		abc[3];
	if (argc != 4)
		return (write(1, "\n", 1), 0);
	
	abc[0] = atoi(argv[1]);
	abc[1] = atoi(argv[3]);
	if (argv[2][0] == '+')
		abc[2] = abc[0] + abc[1];
	else if (argv[2][0] == '-')
		abc[2] = abc[0] - abc[1];
	else if (argv[2][0] == '*')
		abc[2] = abc[0] * abc[1];
	else if (argv[2][0] == '/')
		abc[2] = abc[0] / abc[1];
	printf("%d\n", abc[2]);
	//write(1, "\n", 1);
	return (0);
}