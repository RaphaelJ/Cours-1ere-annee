#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592

int main(void) 
{
	int rayon, hauteur;
	
	printf("Entrez le rayon d'un cylindre: ");
	scanf("%d", &rayon);

	printf("Entrez la hauteur d'un cylindre: ");
	scanf("%d", &hauteur);

	printf("Volume: %.2f et Surface: %.2f\n",
		PI * rayon * rayon * hauteur, /* Volume */
		2 * PI * rayon * rayon + (2 * PI * rayon) * hauteur); /* Surface */
		/*¨		Bases					Cote				*/

	return 0;
}
