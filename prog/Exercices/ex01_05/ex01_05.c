#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int nb_jours;
	float capital, taux, interet;

	printf("Capital de depart: ");
	scanf("%f", &capital);

	printf("Taux du compte: ");
	scanf("%f", &taux);
	
	printf("Nombre de jours: ");
	scanf("%d", &nb_jours);

	interet = (capital * taux * (float) nb_jours) / (360 * 100);

	printf("Le capital sera apres %d jours de %.2f\n",
		nb_jours,
		capital + interet);

	return 0;
}
