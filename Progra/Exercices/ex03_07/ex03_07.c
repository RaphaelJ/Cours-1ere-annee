#include <stdio.h>

int main (void) 
{
	int nbre, old_nbre;
	char restart;

	do {
		nbre = 0;

		printf("Entrez des nombres par ordre croissant\n");
		
		do {
			old_nbre = nbre;
			printf("Entrez un nombre superieur ou egal a %d: ",
				old_nbre);
			scanf("%d", &nbre);
		} while (nbre >= old_nbre);

		printf("Fin de saisie\n");

		printf("Continuer (0: Non - 1: Oui) : ");
		scanf("%d", &restart);
	} while (restart);
}