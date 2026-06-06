
#include <stdio.h>

static int ft_isspace(int chr)
{
	if ((chr >= 9 && chr <= 13) || chr == ' ')
		return (1);
	return (0);
}

static int is_numeric(int chr)
{
	if (chr >= '0' && chr <= '9')
		return (1);
	return (0);
}

int ft_atoi(const char *nptr)
{
	int i = 0;
	int num = 0;
	int sign = 1;

	while(ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (is_numeric(nptr[i]) && nptr[i])
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * num);
}

int main(void)
{
	
	printf("%d\n", ft_atoi("-244466666"));
	return (0);
}