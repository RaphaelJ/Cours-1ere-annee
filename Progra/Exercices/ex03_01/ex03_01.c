#include <stdio.h>

int main (void) 
{
	int nombre = 0,
		somme = 0,
		nb_nombres = -1;

	do {
		somme += nombre;
		nb_nombres++;

		printf("Entrez au moins un nombre (-1 pour arreter): ");
		scanf("%d", &nombre);
	} while (nombre >= 0);

	if (nb_nombres <= 0)
		nb_nombres = 1; /* Division par 0 impossible */

	printf("La moyenne de ces nombres vaut %.2f\n",
		somme / (float) nb_nombres);
}