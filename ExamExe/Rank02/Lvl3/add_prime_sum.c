
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

static int is_prime(int nb)
{
	if (nb < 2)
		return (0);
	if (nb == 2 || nb == 3)
		return (1);
	if (nb % 2 == 0 || nb % 3 == 0) 
		return (0);
	int d = 5;
	while (nb >= d * d)
	{
		if (nb % d == 0)
        	return (0);
		d++;
	}
	return (1);
}

int ft_isspace(char chr)
{
	return ((chr >= 9 && chr <= 13) || chr == ' ');
}

static int groot_atoi(char *nptr)
{
	long res = 0;
	size_t i = 0;
		
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		write(1, "0\n", 2);
		exit(0);
	}
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)res);
}



int main(int ac, char *av[])
{
	// if (ac != 2)
	// 	return (write(1, "0\n", 2));
	int sum = 0;
	
	int numb = groot_atoi(av[1]);

	while(numb)
	{
		if (is_prime(numb))
			sum = sum + numb;
		numb--;
	}
	
	printf("%d", sum);
	return (0);
}


