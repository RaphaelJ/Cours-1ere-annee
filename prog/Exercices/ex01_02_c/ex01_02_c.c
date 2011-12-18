#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int petit_cote;
	int grand_cote;
	int hauteur;

	printf("Entrez la longueur du petit cote d'un paralellograme: ");
	scanf("%d", &petit_cote);

	printf("Entrez la longueur du grand cote d'un paralellograme: ");
	scanf("%d", &grand_cote);
	
	printf("Entrez la hauteur d'un parallelogramme: ");
	scanf("%d", &hauteur);

	printf("Le perimetre d'un parallelogramme d'un petit cote de %d, d'un grand cote de %d et d'une hauteur de %d est de %d et son aire est de %d\n",
		petit_cote, grand_cote, hauteur,
		(petit_cote + grand_cote) * 2, /* Perimetre */
		hauteur * grand_cote); /* Surface */

	return 0;
}
