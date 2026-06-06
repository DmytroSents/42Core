
#include <unistd.h>

static int	ft_strchr(int chr, char *str)
{
	size_t	i = 0;

	while (str[i])
	{
		if (chr == str[i])
			return (1);
		i++;
	}
	return (0);
}
int	main(int argc, char *argv[])
{
	size_t	i = 0;
	size_t	len = 0;

	if (argc != 4)
		return (write(1, "\n", 1), 0);
	if (argv[2][1] || argv[3][1])
		return (write(1, "\n", 1), 0);
	while (argv[1][len])
		len++;
	if (!ft_strchr(argv[2][0], argv[1]))
		return (write(1, argv[1], len), write(1, "\n", 1), 0);

	while (argv[1][i])
	{
		if (argv[1][i] != argv[2][0])
			write(1, &argv[1][i], 1);
		else if (argv[1][i] == argv[2][0])
			write(1, &argv[3][0], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}