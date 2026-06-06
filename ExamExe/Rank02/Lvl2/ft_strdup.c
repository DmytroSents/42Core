
#include <stdlib.h>

char    *ft_strdup(char *src)
{
	size_t i = 0;
	size_t len = 0;
	char *dest = NULL;

	while (src[len])
		len++;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
