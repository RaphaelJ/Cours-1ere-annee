#include <stdio.h>

int main(void)
{
	unsigned short i;

	float euro;
	float monnaie[] = {
		500, 200, 100, 50, 20, 10, 5,
		2, 1,
		(float) 0.5, (float) 0.10, (float) 0.05, (float) 0.02, (float) 0.01
	};
	unsigned short a_rendre = 0;

	printf("Montant a rendre: ");
	scanf("%f", &euro);

	for(i = 0; i < 14; i++) { /* TODO: len(tableau) */
		a_rendre = (unsigned int) (euro / monnaie[i]);

		if(a_rendre > 0)
		{
			euro -= a_rendre * monnaie[i];
			
			if(monnaie[i] >= 5) /* Billets */
			{
				printf("%4d billet(s) de %6.2f euro\n", a_rendre, monnaie[i]);
			}
			else /* Pieces */
			{
				printf("%4d pieces(s) de %6.2f euro\n", a_rendre, monnaie[i]);
			}
		}
	}

	return 0;
}