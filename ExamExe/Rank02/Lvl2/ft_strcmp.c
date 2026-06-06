
#include <string.h>
    
int ft_strcmp(const char *s1, const char *s2)
{
	size_t i = 0;
	while ((s1[i] || s2[i]) && ((unsigned int)s1[i] == (unsigned int)s2[i]))
		i++;
	return ((unsigned int)s1[i] - (unsigned int)s2[i]);
}
