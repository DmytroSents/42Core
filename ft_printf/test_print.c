#include "ft_printf.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
	char	str[402] = "The strlen() function calculates the length of the string pointed to_.";

	int		i = 0;		int		max = 13;
	int		mine[77];
	int		orig[77];

	mine[0] = ft_printf(NULL);	orig[0] = 	printf(NULL);	
	mine[1] = ft_printf("%d; %d; %d; %d; %d; %d; %d;\n", 5, 0, -42, INT_MAX, INT_MIN, 20005, INT_MIN - 69);
	orig[1] = printf("%d; %d; %d; %d; %d; %d; %d;\n", 5, 0, -42, INT_MAX, INT_MIN, 20005, INT_MIN - 69);
	mine[2] = ft_printf("%p; %p; %p; %p;\n", NULL, -42, ULONG_MAX, str);
	orig[2] = 	printf("%p; %p; %p; %p;\n", NULL, -42, ULONG_MAX, str);
	mine[3] = ft_printf("\nc%%%H%%%H%HH%H%H%H%D%", '!');
	orig[3] = 	printf("\nc%%%H%%%H%HH%H%H%H%D%", '!');
	mine[4] = ft_printf("\n\t%cc%cc%c\n", 'a', '\t', 'b');
	orig[4] = printf("\n\t%cc%cc%c\n", 'a', '\t', 'b');
	mine[5] = ft_printf("\n%cs%cs%c\n", 'c', 'b', 'a');
	orig[5] = printf("\n%cs%cs%c\n", 'c', 'b', 'a');
	mine[6] = ft_printf("%ss%ss%ss\n", "And ", "some other", "joined");
	orig[6] = printf("%ss%ss%ss\n", "And ", "some other", "joined");
	mine[7] = ft_printf("\t%s\n", (char *)NULL);
	orig[7] = printf("\t%s\n", (char *)NULL);
	mine[8] = ft_printf("%pp%p%p\n", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	orig[8] = printf("%pp%p%p\n", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	mine[9] = ft_printf("%i; %iii%%i%i; %i; %i \n", -6000023, INT_MAX, INT_MIN, 0, -2004200);
	orig[9] = printf("%i; %iii%%i%i; %i; %i \n", -6000023, INT_MAX, INT_MIN, 0, -2004200);
	mine[10] = ft_printf("%u; %uii%%i%u; %u; %u %u\n", -6000023, INT_MAX, INT_MIN, 0, -2004200, UINT_MAX);
	orig[10] = printf("%u; %uii%%i%u; %u; %u %u\n", -6000023, INT_MAX, INT_MIN, 0, -2004200, UINT_MAX);
	mine[11] = ft_printf("dgs%xxx; %x; %x; %x; %x; %x; %x; %x \n", 1007, INT_MAX, UINT_MAX, INT_MIN, 0x7fedcba1 ,-42 ,0xabcdef ,0 );
	orig[11] = printf("dgs%xxx; %x; %x; %x; %x; %x; %x; %x \n", 1007, INT_MAX, UINT_MAX, INT_MIN, 0x7fedcba1 ,-42 ,0xabcdef ,0 );
	mine[12] = ft_printf("dgs%XXX; %X; %X; %X; %X; %X; %X; %X \n", 1007, INT_MAX, UINT_MAX, INT_MIN, 0x7fedcba1 ,-42 ,0xabcdef ,0 );
	orig[12] = printf("dgs%XXX; %X; %X; %X; %X; %X; %X; %X \n", 1007, INT_MAX, UINT_MAX, INT_MIN, 0x7fedcba1 ,-42 ,0xabcdef ,0 );
	mine[13] = ft_printf("");
	orig[13] = printf("");
	while (i <= max - 0) {	printf("\vMine: %d; Orig: %d\n", mine[i], orig[i]);	i++; }
	
	//printf("\vMine: %d;\n__Orig: %d\n", mine[3], orig[3]);
	
	return (0);
}

