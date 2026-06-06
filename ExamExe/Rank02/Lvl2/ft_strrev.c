
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static size_t ft_strlen(char *str)
{
	size_t i = 0;
	while(str[i])
		i++;
	return (i);
}
char    *ft_strrev(char *str)
{
	size_t	i = 0;
	char	tmp;
	size_t	len = ft_strlen(str);	
	while (i <= len / 2)
	{
		tmp = str[i];
		str[i] = str[len - i - 1];	
		str[len - i - 1] = tmp;
		i++;
	}
	return (str);
}

int main(int ac, char *av[])
{
	//printf("%s\n", av[1]);
	char *str = strdup(av[1]);

	printf("%s\n", ft_strrev(str));
	return (0);
}