#include <stdio.h>

int main (void)
{
	int res1, res2, res3;

	printf("Entrez la valeur de la premiere resistance: ");
	scanf("%d", &res1);

	printf("Entrez la valeur de la deuxieme resistance: ");
	scanf("%d", &res2);

	printf("Entrez la valeur de la troisieme resistance: ");
	scanf("%d", &res3);

	printf("Mise en serie, elles donnent une resistance equivalente a %d omhs",
		res1 + res2 + res3);

	printf("Mise en paralelle, elles donnent une resistance equivalente a %d omhs",
		(float) 1 / res1 + (float) 1 / res3 + (float) 1 / res3);

	return 0;
}
