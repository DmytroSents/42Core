
#include <stdlib.h>

static int ft_strchr(int chr, char* str)
{
	while (*str && *str != chr)
		str++;
	if (*str == chr)
		return (1);
	return (0);
}

char	*ft_strpbrk(const char *s1, const char *s2)
{
	size_t i = 0;
	while (s1[i] && !ft_strchr(s1[i], s2))
		i++;
	if (s1[i] && ft_strchr(s1[i], s2))
		return ((char *)(s1 + i));
	return (NULL);
}