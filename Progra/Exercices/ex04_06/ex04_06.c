#include <stdio.h>

#define MAX_ARRAY_SIZE 30

int main (void)
{
	int nbLgn, nbCol, iLgn, iCol,
		tab[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
		vecLgn[MAX_ARRAY_SIZE] = {0},
		vecCol[MAX_ARRAY_SIZE] = {0},
		vecDia[MAX_ARRAY_SIZE] = {0};

	printf("Nombre de lignes : ");
	scanf("%d", &nbLgn);

	printf("Nombre de colonnes : ");
	scanf("%d", &nbCol);

	for (iLgn = 0; iLgn < nbLgn; iLgn++)
	{
		for (iCol = 0; iCol < nbCol; iCol++)
		{
			printf("Valeur de la cellule [%d][%d] : ",
				iLgn, iCol);
			scanf("%d", &tab[iLgn][iCol]);
		}
	}

	printf("== Somme des lignes ==\n");

	for (iLgn = 0; iLgn < nbLgn; iLgn++)
	{
		for (iCol = 0; iCol < nbCol; iCol++)
		{
			vecLgn[iLgn] += tab[iLgn][iCol];
		}
		printf("%d\n", vecLgn[iLgn]);
	}

	printf("== Sommes des colonnes ==\n");

	for (iCol = 0; iCol < nbCol; iCol++)
	{
		for (iLgn = 0; iLgn < nbLgn; iLgn++)
		{
			vecCol[iCol] += tab[iLgn][iCol];
		}
		printf("%d\t", vecCol[iCol]);
	}
	printf("\n");

	printf("== Somme des diagonales ==\n");

	for (iCol = 0; iCol < nbCol; iCol++)
	{
		for (iLgn = 0; iLgn < nbLgn; iLgn++)
		{
			vecDia[iCol] += tab[iLgn][(iCol + iLgn) % nbCol];
		}
		printf("%d\n", vecDia[iCol]);
	}

	return 0;
}