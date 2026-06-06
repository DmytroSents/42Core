
#include <unistd.h>
#include <stdio.h>

static int is_lower(int chr)
{
	return (chr >= 'a' && chr <= 'z');
}

int main(int ac, char *av[])
{
	// if (ac != 2)
	// 	return (write(1, "\n", 1), 0);

	size_t i = 0;
	size_t j = 0;
	char	out;

	while (av[1][i])
	{
		if (is_lower(av[1][i]))
			write(1, &av[1][i], 1);
		else if (av[1][i] == '_')
		{
			i++;
			out = av[1][i] - 32;
			write(1, &out, 1);
		}
		i++;

	}

	
	write(1, "\n", 1);
	return (0);
}