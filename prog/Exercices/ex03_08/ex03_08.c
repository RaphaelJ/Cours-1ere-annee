#include <stdio.h>

int main (void) 
{
	int nbre, old_nbre;
	char restart, desc;

	do {
		old_nbre = nbre = 0;

		printf("Entrez des nombres par ordre croissant\n");
		
		do {
			if (nbre < old_nbre)
				desc = 1;
			else
				desc = 0;

			old_nbre = nbre;
			printf("Entrez un nombre superieur ou egal a %d: ",
				old_nbre);
			scanf("%d", &nbre);
		} while (nbre >= old_nbre || (nbre < old_nbre && !desc));

		printf("Fin de saisie\n");

		printf("Continuer (0: Non - 1: Oui) : ");
		scanf("%d", &restart);
	} while (restart);
}