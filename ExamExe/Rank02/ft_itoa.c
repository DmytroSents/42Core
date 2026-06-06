
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

static int ft_lenght(long nb)
{
	int len = 1;

	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}
char	*ft_itoa(int nbr)
{
	size_t	i = 0;
	long	temp = nbr;
	char	*numb_s = NULL;

	int len = ft_lenght(temp);
	numb_s = (char *)malloc(len + 1);
	if (!numb_s)
		return (NULL);
	numb_s[len--] = '\0';
	if (nbr < 0)
	{
		temp = -1 * temp;
		numb_s[0] = '-';
	}
	
	while (temp)
	{
		numb_s[len] = (temp % 10) + '0';
		temp = temp / 10;
		len--;
	}
	return (numb_s);
}

// int main()
// {
// 	printf("%s\n", ft_itoa(-778890));
// }