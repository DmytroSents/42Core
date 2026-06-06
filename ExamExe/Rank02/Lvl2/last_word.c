
#include <unistd.h>

static int	ft_isspace(char c)
{
	return ((c == '\t'|| c == ' '));
}

int main (int ac, char *av[])
 {
	size_t i = 0;
	
	if (ac != 2)
		return (write(1, "\n", 1), 0);

	char *last = av[1];
	
	while (*av[1])
	{
		while (ft_isspace(*av[1]) && *av[1])
			av[1]++;
		if (!ft_isspace(*av[1]) && *av[1])
			last = av[1];
		while (!ft_isspace(*av[1]) && *av[1])
			av[1]++;
	}
	while(last[i] && last[i] != ' ' && last[i] != '\t')
		i++;
	write(1, last, i);
	write(1, "\n", 1);
	return (0);
 }
