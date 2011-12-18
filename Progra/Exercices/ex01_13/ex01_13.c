#include <stdio.h>
#include <math.h>

#define DIVISEUR_COMPTE 97

short reste(double dividente, int diviseur); /* Donne le reste de la division entiere de dividente sur diviseur */

int main(void)
{
	double compte;
	unsigned short controle, computed_controle;

	printf("Entrez les dix premiers chiffres de votre numero de compte:\n");
	scanf("%lf", &compte);

	printf("Entrez les deux derniers chiffres de votre numero de compte:\n");
	scanf("%d", &controle);


	if((computed_controle = reste(compte, DIVISEUR_COMPTE)) != controle)
	{
		printf("Compte invalide\nPeut etre est-ce %.lf-%d ?\n", compte,
			computed_controle);

		/* correcteur(compte, controle); 
		 * => Correcteur impossible car les divisions des doubles ne sont pas exactes
		 * et produit des résultats aléatoires
		 */ 

		return 1;
	}

	printf("Compte valide\n");
	return 0;
}

short reste(double dividente, int diviseur) /* Donne le reste de la division entiere de dividente sur diviseur */
{
	return (short) (dividente - (int) (dividente / diviseur) * diviseur);
}
