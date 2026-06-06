
#include <stdlib.h>
#include <stdio.h>

int		*ft_range(int start, int end)
{
	int i = 0;
	int amount = 0;
	while (start + amount <= end)
		amount++;
	int *tab = (int *)malloc(amount * sizeof(int));

	while (start <= end)
	{
		tab[i++] = start;
		start++;

	}
	return(tab);
}

int main()
{
	printf("%d\n", ft_range(1, 5));
}