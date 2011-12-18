#include<stdio.h>

int main (void)
{
	int annee;
	short mois;

	printf("Entrez un mois: ");
	scanf("%d", &mois);

	if (mois == 2)
	{
		printf("Entrez une annee: ");
		scanf("%d", &annee);

		if (annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0)) /* Annee bissextile */
		{
			printf("Il y a 29 jours dans ce mois\n");
		}
		else
		{
			printf("Il y a 28 jours dans ce mois\n");
		}
	}
	else if ((mois <= 7 && mois % 2 == 1) || (mois >= 8 && mois % 2 == 0))
	{
		printf("Il y a 31 jours dans ce mois\n");
	}
	else
	{
		printf("Il y a 30 jours dans ce mois\n");
	}

	return 0;
}