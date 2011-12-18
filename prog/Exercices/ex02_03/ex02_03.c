#include <stdio.h>

int main (void)
{
	int nombre;

	printf("Entrez un nombre: ");
	scanf("%d", &nombre);

	if (nombre % 2 == 0)
	{
		printf("%d est un nombre pair\n",
			nombre);
	}
	else
	{
		printf("%d n'est pas un nombre pair\n",
			nombre);
	}

	return 0;
}