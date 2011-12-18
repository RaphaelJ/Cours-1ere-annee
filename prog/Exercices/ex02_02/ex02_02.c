#include <stdio.h>

int main (void)
{
	int nombre, multiple;

	printf("Entrez un nombre: ");
	scanf("%d", &nombre);

	printf("Entrez un multiple possible: ");
	scanf("%d", &multiple);

	if (multiple % nombre == 0)
	{
		printf("%d est un multiple de %d\n",
			multiple, nombre);
	}
	else
	{
		printf("%d n'est pas un multiple de %d\n",
			multiple, nombre);
	}

	return 0;
}