
#include <unistd.h>
#include <string.h>
#include <stdio.h>


int main(int ac, char *av[])
{
	if (ac != 3)
		return (write(1, "\n", 1), 0);
	
	size_t i = 0;
	size_t j = 0;

	while (av[1][i])
	{
		while (av[2][j])
		{
			if (av[1][i] != av[2][j])
				j++;
			else if (av[1][i] == av[2][j])
			{
				j++;
				break ;
			}
				
		}
		if (!av[2][j])
			break ;
		i++;
	}
	if (!av[1])
		printf("%s", av[1]);
	printf("\n");
	return (0);
}