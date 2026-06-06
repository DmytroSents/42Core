
#include <unistd.h>

static void swap_case(int chr)
{
	if (chr >= 'a' && chr <= 'z')
		chr = chr - 32;
	else if (chr >= 'A' && chr <= 'Z')
		chr += 32;
	write(1, &chr, 1);
}

static int ft_isalpha(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	return (0);
}

int main (int argc, char *argv[])
{
	size_t i = 0;
	if (argc != 2)
		return (write(1, "\n", 1), 0);

	while (argv[1][i])
	{
		if (!ft_isalpha(argv[1][i]))
			write(1, &argv[1][i], 1);
		else if (ft_isalpha(argv[1][i]))
			swap_case(argv[1][i]);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}