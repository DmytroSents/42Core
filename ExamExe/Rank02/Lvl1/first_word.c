
#include <unistd.h>
#include <stdio.h>

static int ft_isalpha(int chr)			/// ???
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (chr);
	return (0);
}

int	main(int argc, char *argv[])
{
	size_t	i = 0;
	size_t	j = 0;
	void	*ptr = NULL; 
	
	if (argc != 2)
		return (write(1, "\n", 1), 0);

	while (argv[1][i] == ' ' || argv[1][i] == '\t')
		i++;
	while ((argv[1][i + j] != ' ' && argv[1][i + j] != '\t') && argv[1][i + j])
		j++;

	ptr = (void *)(argv[1] + i);
	write(1, ptr, j);
	
	//printf("Int i =_%zu; Int j =_%zu\n", i, j);

	write(1, "\n", 1);
	return (0);
}
