#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int cote_carre;

	printf("Entrez la longueur du cote d'un carre: ");
	scanf("%d", &cote_carre);
	
	printf("Le perimetre d'un carre de %d de cote est %d et son aire est %d\n",
		cote_carre,
		cote_carre * 4, /* Perimetre */
		cote_carre * cote_carre); /* Aire */

	return 0;
}