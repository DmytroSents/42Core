
#include <unistd.h>
#include <stdio.h>

static size_t ft_strlen(char *str)
{
	size_t i = 0;

	while (str[i])
		i++;
	return (i);
}

static char *mini_itoa(int i, char *buf)
{
	if (i < 10)
	{
		buf[0] = i + 48;
		buf[1] = '\n';
	}
	else if (i >= 10)
	{
		buf[1] = i % 10 + 48;
		i = i / 10;
		buf[0] = i + 48;
		buf[2] = '\n';
	}
	return (buf);
}

int	main()
{
	int		i = 1;
	char	*out = NULL;
	char 	itoa[4] = {0};
	
	while (i <= 100)
	{
		if ( i % 3 == 0 && i % 5 != 0)
			out = "fizz\n";
		else if ( i % 3 != 0 && i % 5 == 0)
			out = "buzz\n";
		else if ( i % 3 == 0 && i % 5 == 0)
			out = "fizzbuzz\n";
		else 
			out = mini_itoa(i, itoa);
		
		write(1, out, ft_strlen(out));
		i++;
	}
	return (0);
}