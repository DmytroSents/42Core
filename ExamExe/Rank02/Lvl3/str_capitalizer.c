
#include <unistd.h>
#include <stdio.h>

static int is_space(int c)
{
	return (c == ' ' || c == '\t');
}

static int which_case(int chr)
{
	if (chr >= 'a' && chr <= 'z')
		return ('l');
	else if (chr >= 'A' && chr <= 'Z')
		return ('U');
	return (0);
}
static int putchr(int c)
{
	return (write(1, &c, 1));
}

static int put_tolower(int c)
{
	if (c >= 'A' && c<= 'Z')
		return (putchr(c + 32));
	return (putchr(c));
}

static void ft_capitalize(const char *str)
{
	size_t i = 0;

	while(str[i])
	{
	while(str[i] && is_space(str[i]))
	{	putchr(str[i]);		i++;	}
	if (str[i] && which_case(str[i]))
	{	if (which_case(str[i]) == 'l')
			putchr(str[i] - 32);
		else
			putchr(str[i]);
		i++;
	}
	while (str[i] && !is_space(str[i]))
	{	put_tolower(str[i]); 	i++;	}
	}

}

int main(int ac, char *av[])
{
	if (ac < 2)
		return (write(1, "\n", 1));

	int i = 0;
	while (av[i])
	{
		ft_capitalize(av[i]);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
