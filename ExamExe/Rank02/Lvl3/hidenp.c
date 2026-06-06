
#include <unistd.h>
#include <stdio.h>

// static int ft_strchr(char *s, int c)
// {
// 	size_t i = 0;
// 	while(s[i] && s[i] != c)
// 		i++;
// 	return (s[i]);
// }
int main(int ac, char *av[])
{
	if (ac != 3)
		return (write(1, "\n", 1) * 0);

	int len = 0;
	int bull = 0;
	size_t i = 0;
	size_t j = 0;

	while(av[1][len])
		len++;
	while (av[1][i])
	{
		while(av[2][j])
		{
			if (av[1][i] == av[2][j])
			{	bull++;	break ;		}
			j++;
		}
		i++;
	}
	if (len == bull)
		write(1, "1", 1);
	else 
		write(1, "0", 1);
	
	write(1, "\n", 1);
}