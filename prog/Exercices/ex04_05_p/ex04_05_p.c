#include <stdio.h>

#define MAX_ARRAY_SIZE 30

int main (void)
{
	int nbLgn, nbCol, iLgn, iCol,
		tab[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], *pTab;

	printf("Nombre de lignes : ");
	scanf("%d", &nbLgn);

	printf("Nombre de colonnes : ");
	scanf("%d", &nbCol);

	for (pTab = &tab[0][0]; pTab < (&tab[0][0] + (nbLgn * MAX_ARRAY_SIZE)); pTab++)
	{
		if ((pTab - &tab[0][0]) % nbCol < nbCol)
		{
			printf("Valeur de la cellule [%d][%d] : ",
				(pTab - &tab[0][0]) / MAX_ARRAY_SIZE,
				(pTab - &tab[0][0]) % MAX_ARRAY_SIZE);
			scanf("%d", pTab);
		}
	}

	printf("== Affichage en lignes ==\n");

	for (iLgn = 0; iLgn < nbLgn; iLgn++)
	{
		for (iCol = 0; iCol < nbCol; iCol++)
		{
			printf("%d\t", tab[iLgn][iCol]);
		}
		printf("\n");
	}

	printf("== Affichage en colonnes ==\n");

	for (iCol = 0; iCol < nbCol; iCol++)
	{
		for (iLgn = 0; iLgn < nbLgn; iLgn++)
		{
			printf("%d\t", tab[iLgn][iCol]);
		}
		printf("\n");
	}

	printf("== Affichage en diagonale ==\n");

	for (iCol = 0; iCol < nbCol; iCol++)
	{
		for (iLgn = 0; iLgn < nbLgn; iLgn++)
		{
			printf("%d\t", tab[iLgn][(iCol + iLgn) % nbCol]);
		}
		printf("\n");
	}

	return 0;
}