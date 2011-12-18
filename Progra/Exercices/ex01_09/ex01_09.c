#include <stdio.h>

int main(void)
{
	unsigned int sec;
	unsigned short h, m, min;

	printf("Entrez un nombre de secondes: ");
	scanf("%d", &sec);

	h = sec / 3600;
	sec -= h * 3600;
	min = sec / 60;
	sec -= min * 60;

	printf("%dh. %dmin. %dsec.\n",
		h, min, sec);

	return 0;
}