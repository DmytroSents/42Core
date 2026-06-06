
#include <unistd.h>

static int is_upper(int chr)
{
	if (chr >= 'A' && chr <= 'Z')
		return (1);
	return (0);
}

static int is_lower(int chr)
{
	if (chr >= 'a' && chr <= 'z')
		return (1);
	return (0);
}

int main(int argc, char *argv[])
{
	size_t	i = 0;
	int		chr;
	if (argc != 2)
		return (write(1, "\n", 1), 0);
	while (argv[1][i])
	{
		if (!is_upper(argv[1][i]))
			write(1, &argv[1][i], 1);
		else if (is_upper(argv[1][i]))
		{
			write(1, "_", 1);
			chr = 'a' - 'A' + argv[1][i];
			write(1, &chr, 1);
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}