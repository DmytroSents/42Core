
#include <unistd.h>
#include <stdio.h>

int main(int ac, char *av[])
{
	if (ac != 2)
		return (write(1, "\n", 1));
	size_t i = 0;
	size_t len = 0;

	while ((av[1][i] == '\t' || av[1][i] == ' ') && av[1][i])	// skip spaces at the begining 
			i++;
	while (av[1][len])
		len++;
	len = len - 1;
	while ((av[1][len] == '\t' || av[1][len] == ' ') && av[1][i])	//skip spaces at the end
		len--;
	len++;
	while (av[1][i] && (&av[1][i] != &av[1][len]))
	{
		while ((av[1][i] == '\t' || av[1][i] == ' ') && av[1][i])
		{
			i++;
			if ((av[1][i] != '\t' && av[1][i] != ' ') && av[1][i])
				write(1, "   ", 3);
		}
		if ((av[1][i] != '\t' && av[1][i] != ' ') && av[1][i])
		{	write(1, &av[1][i], 1);			}
		
		i++;
	}
	//printf("%p; %p", &av[1][i], &av[1][len]);
	return (0);
}





