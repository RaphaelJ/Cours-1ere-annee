#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int long_rect;
	int haut_rect;

	printf("Entrez la longueur d'un rectangle: ");
	scanf("%d", &long_rect);
	
	printf("Entrez la hauteur d'un rectangle: ");
	scanf("%d", &haut_rect);

	printf("Le perimetre d'un rectangle de %d sur %d est %d et son aire est %d\n",
		long_rect, haut_rect,
		(long_rect + haut_rect) * 2, /* Perimetre */
		long_rect * haut_rect); /* Aire */

	return 0;
}
