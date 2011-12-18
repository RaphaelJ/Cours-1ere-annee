#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592

int main(void) 
{
	int rayon;

	printf("Entrez le rayon d'un cercle: ");
	scanf("%d", &rayon);

	printf("Le perimetre d'un cercle de rayon %d est de %f et son aire est de %f\n",
		rayon, 2 * PI * rayon, /* Perimetre */
		PI * (rayon * rayon)); /* Aire */

	return 0;
}
