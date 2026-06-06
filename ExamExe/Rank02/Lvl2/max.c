
#include <stdio.h>
#include <limits.h>

int		max(int* tab, unsigned int len)
{
	if (len <= 0)
		return (0);
	int	max_n = INT_MIN;

	unsigned int i = 0;
	while (i < len)
	{
		if (tab[i] > max_n)
			max_n = tab[i];
		i++;
	}
	return (max_n);
}
int main (int ac, char *av[])
 {
	printf("%lu\n", sizeof(unsigned int));
	printf("%lu\n", sizeof(size_t));
	return (0);
 }