#include <stdio.h>

int main (void)
{
	int nombre1, nombre2;

	printf("Entrez un premier nombre: ");
	scanf("%d", &nombre1);

	printf("Entrez un deuxieme nombre: ");
	scanf("%d", &nombre2);

	if (nombre1 > nombre2)
	{
		printf("%d est plus grand que %d\n",
			nombre1, nombre2);
	}
	else if (nombre2 > nombre1)
	{
		printf("%d est plus grand que %d\n",
			nombre2, nombre1);
	}
	else
	{
		printf("%d et %d sont les deux mêmes nombres\n",
			nombre1, nombre2);
	}

	return 0;
}