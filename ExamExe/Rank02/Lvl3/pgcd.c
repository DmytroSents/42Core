
#include <unistd.h>
#include <stdio.h>

static int mini_atoi(const char *nptr)
{
	size_t i = 0;
	int result = 0;

	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result);
}

static void mini_putnbr(int nb)
{
	char out;

	if (nb == 0)
	{	write(1, "0", 1); return ;	}
	if (nb >= 10)
	mini_putnbr(nb / 10);

	out = nb % 10 + '0';
	write(1, &out, 1);
}

int find_HCD(int a, int b)
{
	if (!a || !b)
		return (0);

	int HCD;

	if (a > b)
		HCD = b;
	else if (b > a)
		HCD = a;

	while (--HCD > 1)
	{
		if (a % HCD == 0 && b % HCD == 0)
			return (HCD);
	}

	return (1);
}

int main(int ac, char *av[])
{
	if (ac != 3)
		return (write(1, "\n", 1));
	mini_putnbr(find_HCD(mini_atoi(av[1]), mini_atoi(av[2])));
	write(1, "\n", 1);

}
