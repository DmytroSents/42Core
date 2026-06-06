
#include <unistd.h>
#include <stdio.h>

static int atoi10(const char *nstr)
{
	int result = 0;
	size_t i = 0;

	while(nstr[i])
	{
		result = result * 10 + (nstr[i] - '0');
		i++;
	}
	return (result);
}

static int ft_strchr(char *s, int c) 	// c == '?';
{
	size_t i = 0;
	while (s[i] && s[i] != c)
		i++;
	return(s[i]);
}
static void itohex(int nb)
{
	if (nb == 0)
	{	write(1, "0", 1); return ;	}
	char out;
	int base = 16;
	char set[17] = "0123456789abcdef";
	
	if(nb >= base)
	{
		//out = set[nb % base];
		itohex(nb / base);
	}


	write(1, &set[nb % base], 1);

}

int main(int ac, char *av[])
{
	if (ac != 2)
		return(write(1, "\n", 1) * 0);

	itohex(atoi10(av[1]));
	write(1, "\n", 1);
}