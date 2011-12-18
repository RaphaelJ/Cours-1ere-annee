#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int cote_1, pond_cote_1, cote_2, pond_cote_2;

	printf("Premiere cote: ");
	scanf("%d", &cote_1);

	printf("Ponderation cote 1: ");
	scanf("%d", &pond_cote_1);
	
	printf("Deuxieme cote: ");
	scanf("%d", &cote_2);

	printf("Ponderation cote 2: ");
	scanf("%d", &pond_cote_2);

	printf("Moyenne de %d (pond. %d) et %d (pond. %d) est %.2f\n",
		cote_1, pond_cote_1, cote_2, pond_cote_2, 
		(float) (cote_1 * pond_cote_1 + cote_2 * pond_cote_2) / (pond_cote_1 + pond_cote_2)); /* Moyenne */

	return 0;
}
