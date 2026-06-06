
#include <unistd.h>
#include <stdio.h>

int main(int ac, char *av[])
{
	if (ac != 3)
		return (write(1, "\n", 1), 0);
	
	size_t i = 0;
	size_t j = 0;
	int orig[256] = {0};
	while (av[1][i])
	{
		if (av[1][i] && !orig[(int)av[1][i]])
		{
			write(1, &av[1][i], 1);
			orig[(int)av[1][i]] = 1;
		}
		i++;
	}
	while (av[2][j])
	{
		if (av[2][j] && !orig[(int)av[2][j]])
		{
			write(1, &av[2][j], 1);
			orig[(int)av[2][j]] = 1;
		}
		j++;
	}
	write(1, "\n", 1);
	return (0);
}