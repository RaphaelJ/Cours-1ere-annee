#include<stdio.h>

int main (void)
{
	char jour, mois;
	int annee;

	/* Annee */
	printf("Entrez une annee: ");
	scanf("%d", &annee);
	
	if (annee == 0)
	{
		printf("Il n'y a pas d'an 0\n");
		return 1;
	}

	/* Mois */
	printf("Entrez un mois: ");
	scanf("%d", &mois);

	if (mois < 1 || mois > 12)
	{
		printf("Le mois dois avoir une valeur entre 1 et 12\n");
		return 1;
	}

	/* Jour */
	printf("Entrez un jour: ");
	scanf("%d", &jour);

	if (jour < 1)
	{
		printf("Le jour doit etre supperieur ou egal a 1\n");
		return 1;
	}
	/* else */ /* else inutile */
	if ((mois == 2 && jour > 28
		 && (jour > 29  /* En fevrier, plus de 29 jours ou annee non bissextile et 29 jours */ 
		     || !(annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0))))
		|| (jour > 31 || (jour > 30 /* Plus de 31 jours ou 31 jours dans un mois de 30 */
		                  && !((mois <= 7 && mois % 2 == 1) || (mois >= 8 && mois % 2 == 0)))))
	{
		printf("Il y a trop jours pour ce mois\n");
		return 1;
	}

	printf("Date valide\n");

	return 0;
}