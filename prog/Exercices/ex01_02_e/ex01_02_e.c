#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int base, hauteur, cote1, cote2;

	printf("Base du triangle: ");
	scanf("%d", &base);
	
	printf("Hauteur du triangle: ");
	scanf("%d", &hauteur);

	printf("Premier cote (hors base) du triangle: ");
	scanf("%d", &cote1);

	printf("Deuxieme cote du triangle: ");
	scanf("%d", &cote2);

	printf("Perimetre: %d Aire: %.2f\n",
		base + cote1 + cote2, /* Perimetre */
		(float) (base * hauteur) / 2); /* Aire */

	return 0;
}
