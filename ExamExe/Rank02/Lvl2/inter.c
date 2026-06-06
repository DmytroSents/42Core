
 #include <unistd.h>
 #include <stdio.h>

 static int ft_strchr(int chr, char *str)
 {
	while(*str && *str != chr)
		str++;
	if (*str && *str == chr)
		return (1);
	return (0);
 }
 int main (int ac, char *av[])
 {
	if (ac != 3)
		return (write(1, "\n", 1), 0);
	char orig[256] = {0};
	size_t i = 0;
	size_t j = 0;
	while( av[1][i])
	{
		if (ft_strchr(av[1][i], av[2]) && !ft_strchr(av[1][i], orig))
		{
			orig[j++] = av[1][i];
			write(1, &av[1][i], 1);
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
 }