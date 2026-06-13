//#include "ft_printf.h"

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>

// char	*vibe_itoa(int value, char *result, int base)
// {
// 	char		*ptr;
// 	char		*end;
// 	unsigned int	v;
// 	int			sign;

// 	if (base < 2 || base > 36)
// 	{
// 		*result = '\0';
// 		return (result);
// 	}
// 	ptr = result;
// 	end = result;
// 	sign = 0;
// 	if (value < 0)
// 		sign = 1;
// 	v = value;
// 	if (sign == 1)
// 		v = -value;
// 	while (v != 0)
// 	{
// 		*ptr = (v % base);
// 		if (*ptr < 10)
// 			*ptr = *ptr + '0';
// 		else
// 			*ptr = *ptr + 'a' - 10;
// 		ptr = ptr + 1;
// 		v = v / base;
// 	}
// 	if (sign == 1)
// 	{
// 		*ptr = '-';
// 		ptr = ptr + 1;
// 	}
// 	*ptr = '\0';
// 	ptr = ptr - 1;
// 	while (end < ptr)
// 	{
// 		v = *end;
// 		*end = *ptr;
// 		*ptr = v;
// 		end = end + 1;
// 		ptr = ptr - 1;
// 	}
// 	return (result);
// }
static void	vibe_itoa_fill(unsigned int v, char *ptr, int sign, int base)
{
	while (v != 0)
	{
		*ptr = (v % base);
		if (*ptr < 10)
			*ptr = *ptr + '0';
		else
			*ptr = *ptr + 'a' - 10;
		ptr = ptr + 1;
		v = v / base;
	}
	if (sign == 1)
	{
		*ptr = '-';
		ptr = ptr + 1;
	}
	*ptr = '\0';
}

static char	*vibe_itoa_end(char *start)
{
	char	*ptr;

	ptr = start;
	while (*ptr != '\0')
		ptr = ptr + 1;
	ptr = ptr - 1;
	while (start < ptr)
	{
		*start = *start ^ *ptr;
		*ptr = *start ^ *ptr;
		*start = *start ^ *ptr;
		start = start + 1;
		ptr = ptr - 1;
	}
	return (start);
}

char	*vibe_itoa(int value, char *result, int base)
{
	unsigned int	v;
	int				sign;

	if (base < 2 || base > 36)
		return (*result = '\0', result);
	sign = 0;
	if (value < 0)
		sign = 1;
	v = value;
	if (sign == 1)
		v = -value;
	if (v == 0)
	{
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	vibe_itoa_fill(v, result, sign, base);
	vibe_itoa_end(result);
	return (result);
}

int main (int ac, char *av[])
 {
	int BUFF_SIZE = 77;
	char buffer[BUFF_SIZE];
	printf("%s\n", vibe_itoa(6767, buffer, 10));
	return 0;
}
