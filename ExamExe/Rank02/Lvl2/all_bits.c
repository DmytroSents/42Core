
#include <unistd.h>

void	print_bits(unsigned char oct)
{
	for (int i = 7; i >= 0; i--){
		if ((oct >> i) & 1)
			write(1, "1", 1);
		else 
			write(1, "0", 1);
	}
}

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char tmp;
	unsigned char res = 0;

	int i = 8;
	while (i--)
	{
		tmp = octet >> i;
		tmp = tmp << 7;
		tmp = tmp >> i;
		res = res + tmp;
	}
	return (res);
}

unsigned char	swap_bits(unsigned char octet)
{
	unsigned char left_half = octet << 4;
	unsigned char right_half = octet >> 4;
	return (left_half + right_half);
}

int main(void)
{
	print_bits(57);
	write(1, "\n", 1);
	print_bits(reverse_bits(57));
	return (0);
}
