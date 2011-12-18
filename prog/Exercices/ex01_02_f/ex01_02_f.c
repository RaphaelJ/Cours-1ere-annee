#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int largeur, hauteur, profondeur;
	
	printf("Entrez la largeur d'un volume: ");
	scanf("%d", &largeur);

	printf("Entrez la hauteur d'un volume: ");
	scanf("%d", &hauteur);

	printf("Entrez la profondeur d'un volume: ");
	scanf("%d", &profondeur);

	printf("Volume: %d et Surface: %d\n",
		largeur * hauteur * profondeur, /* Volume */
		2 * (largeur * hauteur + profondeur * largeur + hauteur * profondeur)); /* Surface */

	return 0;
}
