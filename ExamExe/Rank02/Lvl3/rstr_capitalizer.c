
#include <unistd.h>
#include <stdio.h>

static int putchr(int c)
{
	return (write(1, &c, 1));
}

static int is_space(int ch)
{
	return (ch == '\t' || ch == ' ');
}

// static int which_case(int chr)
// {
// 	if (chr >= 'a' && chr <= 'z')
// 		return ('l');
// 	else if (chr >= 'A' && chr <= 'Z')
// 		return ('U');
// 	return (0);
// }
static int put_tolower(int chr)
{
	if (chr >= 'A' && chr <= 'Z')
		return (putchr(chr + 32));
	return (putchr(chr));
}

static int put_toupper(int chr)
{
	if (chr >= 'a' && chr <= 'z')
		return (putchr(chr - 32));
	return (putchr(chr));
}

int ft_capitalize(const char *str)
{
	size_t i = 0;
	while (str[i])
	{
		while (is_space(str[i]))
			putchr(str[i++]);
		while (str[i] && !(is_space(str[i + 1]) || !str[i + 1]))
			put_tolower(str[i++]);
		if ((str[i]))
			put_toupper(str[i++]);
		//else if ()
	}
	
	
	return(write(1, "\n", 1));
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return (write(1, "\n", 1));

	int i = 1;
	while (argv[i])
		ft_capitalize(argv[i++]);
	//ft_capitalize(argv[1]);
	return 0;
}