
#include <unistd.h>
#include <stdio.h>

static size_t	ft_strlen(char *str)
{
	size_t i = 0;

	while (str[i])
		i++;
	return (i);
}

int	main(int argc, char *argv[])
{
	size_t	i = 0;
	size_t len = 0;

	if (argc != 2)
		return (write(1, "\n", 1), 0);
	len = ft_strlen(argv[1]);

	while(len >= 1)
	{	
		write(1, &argv[1][len - 1], 1);
		len = len - 1;
	}
	write (1, "\n", 1);
	return (0);
}