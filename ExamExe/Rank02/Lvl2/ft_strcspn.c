
#include <unistd.h>

static int ft_strchar(int chr, char* str)
{
	size_t i = 0;

	while (str[i])
	{
		if (str[i] == chr)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t i = 0;

	while (s[i] && !ft_strchr(s[i], reject))
			i++;
	return (i);
}
