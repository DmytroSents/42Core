
#include <unistd.h>

static int	which_alpha(int chr)
{
	if (chr >= 'a' && chr <= 'z')
		return ('l');
	else if (chr >= 'A' && chr <= 'Z')
		return ('U');
	return (0);
}

static int	ft_rotone(int chr, int flag)
{
	size_t	i = 0;
	char	*set;

	if (flag == 'l')
		set = "abcdefghijklmnopqrstuvwxyz";
	else if (flag == 'U')
		set = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	while (set[i])
	{
		if (set[i] == chr)
			break ;
		i++;
	}
	if ((i + 1) <= 25)
		write(1, &set[i + 1], 1);
	else if ((i + 1) > 25)
		write(1, &set[0], 1);
	return (i);
}

int	main(int argc, char *argv[])
{
	size_t	i = 0;
	size_t	j = 0;

	if (argc != 2)
		return (write(1, "\n", 1), 0);
	
	while (argv[1][i])
	{
		if (!which_alpha(argv[1][i]))
			write(1, &argv[1][i], 1);
		else if (which_alpha(argv[1][i]))
			ft_rotone(argv[1][i], which_alpha(argv[1][i]));
		i++;
	}	
	
	write (1, "\n", 1);
	return (0);
}