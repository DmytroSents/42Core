
#include <unistd.h>
#include <stdio.h>

static int ft_strchr(char *str, int chr, int flag)
{
	size_t i = 0;
	while (str[i] && str[i] != chr)
		i++;
	if (flag)
		return (i);
	return (str[i]);
}

int main(int argc, char *av[])
{
	if (argc != 2)
		return (write(1, "\n", 1) * 0);

	size_t i = 0;
	int c = 0;
	char set[2][27] = { "abcdefghijklmnopqrstuvwxyz",
						"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	
	while (av[1][i])
	{
		if (!ft_strchr(set[0], av[1][i], 0) && !ft_strchr(set[1], av[1][i], 0))
			write(1, &av[1][i++], 1);
		if (ft_strchr(set[0], av[1][i], 0) || ft_strchr(set[1], av[1][i], 0))
		{
			if (ft_strchr(set[0], av[1][i], 0))
				c = ft_strchr(set[0], av[1][i], 1) + 1;
			else if (ft_strchr(set[1], av[1][i], 0))
				c = ft_strchr(set[1], av[1][i], 1) + 1;
			while (c)
			{
				write(1, &av[1][i], 1);
				c--;
			}
			i++;
		}
	}
	return (write(1, "\n", 1) * 0);
}