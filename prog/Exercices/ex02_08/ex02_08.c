#include <stdio.h>

#define TARIF_1 1000
#define TARIF_2 900
#define TARIF_3 800
#define TARIF_LIVRAISON 150

int main (void)
{
	int nb_ordinateurs, prix_ordinateurs;

	printf("Combien d'ordinateur(s) souhaitez-vous: ");
	scanf("%d", &nb_ordinateurs);

	if (nb_ordinateurs > 200) 
		prix_ordinateurs = (100 * TARIF_1) + (100 * TARIF_2) + ((nb_ordinateurs - 200) * TARIF_3);
	else if (nb_ordinateurs > 100)
		prix_ordinateurs = (100 * TARIF_1) + ((nb_ordinateurs - 100) * TARIF_2);
	else
		prix_ordinateurs = nb_ordinateurs * TARIF_1;

	printf("Total pour %d ordinateur(s):\n",
		nb_ordinateurs);
	printf("Ordinateurs %10d euro\n",
		prix_ordinateurs);
	printf("Livraison %12d euro\n",
		TARIF_LIVRAISON);
	printf("---------------------------\n");
	printf("Total %16d euro\n",
		prix_ordinateurs + TARIF_LIVRAISON);

	return 0;
}