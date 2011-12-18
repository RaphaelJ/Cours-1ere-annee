#include <stdio.h>

#define MAX_ARRAY_SIZE 20

int main (void)
{
	int i;
	char size, iLgn, iCol,
		tab[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0 };

	do {
		printf("Taille du tableau (%d~%d) : ",
			1, MAX_ARRAY_SIZE);
		scanf("%d", &size);
	} while (size < 1 || size > MAX_ARRAY_SIZE);

	for (i = 1; i <= size * size; i++)
	{
		if (i <= 1) /* 1 */
		{
			iLgn = size - 1;
			iCol = size / 2;
		}
		else if (tab[(iLgn + 1) % size][(iCol + 1) % size] != 0) /* case occupée */
		{
			iLgn = iLgn - 1;
		}
		else
		{
			iLgn = (iLgn + 1) % size;
			iCol = (iCol + 1) % size;
		}

		tab[iLgn][iCol] = i;
	}
		

	for (iLgn = 0; iLgn < size; iLgn++)
	{
		for (iCol = 0; iCol < size; iCol++)
			printf("%d\t", tab[iLgn][iCol]);
		printf("\n");
	}


	return 0;
}