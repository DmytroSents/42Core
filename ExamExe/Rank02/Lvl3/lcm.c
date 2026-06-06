
#include <stdio.h>

unsigned int find_GCD(unsigned int n, unsigned int m)
{
	unsigned int GCD;
	if (n == 0 || m == 0)
		return (0);
	if (n >= m )
	 	GCD = m;
	else if (m > n)
		GCD = n;
	while(--GCD)
	{
		if (n % GCD == 0 && m % GCD == 0)
			return GCD;
	}
	return (1);
}

unsigned int    lcm(unsigned int a, unsigned int b)
{
	if (!a || !b)
		return (0);
	unsigned int LCM = a / find_GCD(a, b) * b;

	return (LCM);
}

int main()
{
	
	printf("LCM:%d", lcm(15, 55));
}
