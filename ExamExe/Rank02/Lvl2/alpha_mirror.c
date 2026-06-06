
#include <unistd.h>

static int isalpha_Ul(int chr)
{
	if (chr >= 'a' && chr <= 'z')
		return ('l');
	else if (chr >= 'A' && chr <= 'Z')
		return ('U');
	return (0);
}

static void alpha_mirror(int chr, int flag)
{
	size_t i = 0;
	char	*set;

	if (flag == 'l')
		set = "abcdefghijklmnopqrstuvwxyz";
	else if (flag == 'U')
		set = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	while(set[i])
	{
		if (set[i] == chr)
			break ;
		i++;
	}
	write(1, &set[25 - i], 1);
}

int main(int argc, char *argv[])
{
	size_t i = 0;

	if (argc != 2)
		return (write(1, "\n", 1), 0);
	while (argv[1][i])
	{
		if (!is_alpha_Ul(argv[1][i]))
			write (1, &argv[1][i], 1);
		else if (is_alpha_Ul(argv[1][i]))
			alpha_mirror(argv[1][i], is_alpha_Ul(argv[1][i]));
		i++;
	}
	write(1, "\n", 1);
	return (0);
}