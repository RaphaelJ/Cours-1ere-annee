#include <stdio.h>

int main(void)
{
	int nombres[] = {
		1,
		12,
		123,
		1234,
		12345,
		123456
	};
	
	printf("%6d%d\n", nombres[0], nombres[0]);
	printf("%6d%d\n", nombres[1], nombres[1]);
	printf("%6d%d\n", nombres[2], nombres[2]);
	printf("%6d%d\n", nombres[3], nombres[3]);
	printf("%6d%d\n", nombres[4], nombres[4]);
	printf("%6d%d\n", nombres[5], nombres[5]);
}