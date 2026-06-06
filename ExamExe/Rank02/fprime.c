
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


static int ft_isprime(int nb)
{
	if (nb == 2 || nb == 3 || nb == 5)
		return (1);
	if (nb <= 1 || nb % 2 == 0 || nb % 3 == 0)
		return (0);
	int div = 5; 
	while (div * div <= nb)
	{
		if (nb % div == 0 || nb % (div + 2) == 0)
			return (0);
		div += 6;               /* jump to the next pair 6k‑1, 6k+1 */
	}
	return (1);
}

static int find_next_div(int num)
{
	int div = 2;
	while (div * div <= num)
	{
		if (num % div == 0)
			return (div);
		div++;
	}
	return (0);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (printf("\n") * 0);
	int x = atoi(argv[1]);
	
	if (ft_isprime(x))
		return (printf("%d\n", x));
	
	else if (!ft_isprime(x))
	{
		int div = find_next_div(x);
		while (div)
		{
			printf("%d*", div);
			x = x / div;
			div = find_next_div(x);
			//if (!ft_isprime(x))	printf("*");
			if (ft_isprime(x))
				printf("%d", x);
		}

	}

	return (printf("\n") * 0);
}