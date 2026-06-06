
#include <unistd.h>
#include <stdio.h>

static int mini_atoi(const char *str)
{
	int result = 0;
	size_t i = 0;

	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static int mini_putnb(int nb)
{
	if (nb == 0)
		return (write(1, "0", 1));

	char out;

	if (nb >= 10)
	{
		mini_putnb(nb / 10);
	}
	out = nb % 10 + '0';
	write(1, &out, 1);

	return (0);
}

int main(int ac, char *av[])
{
	if (ac < 2)
		return (write(1, "\n", 1) * 0);
	int target = mini_atoi(av[1]);
	int i = 0;
	
	while (++i <= 9)
	{
		mini_putnb(i); 		write(1, " x ", 3);
		mini_putnb(target);	write(1, " = ", 3);
		mini_putnb(i * target); write(1, "\n", 1);
	}
	return (0);
}