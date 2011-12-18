#include <stdio.h>

int r_abs(int nbre); /* Donne la valeur absolue de nbre */

int main (void) 
{
	int nombre1, nombre2, difference;

	printf("Entrez un premier nombre: ");
	scanf("%d", &nombre1);

	printf("Entrez un deuxieme nombre: ");
	scanf("%d", &nombre2);

	printf("ABS(%d - %d) = %d\n",
		nombre1,
		nombre2,
		r_abs(nombre1 - nombre2));

	return 0;
}

int r_abs(int nbre) /* Donne la valeur absolue de nbre */
{
	return (nbre < 0) * - 1 * nbre + (nbre > 0) * nbre;
}
