#include <stdio.h>

#define MAX_ARRAY_SIZE 20

int main (void)
{
	int numCase;
	char i, size, *pTab, lig, col,
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
			pTab = &tab[0][0];
			pTab += size * (size - 1); /* Dernière ligne */
			pTab += size / 2; /* Case du milieu */
		}
		else
		{
			lig = ((pTab - &tab[0][0]) / size + 1) % size;
			printf("%d\n", pTab - &tab[0][0]);
			col = ((pTab - &tab[0][0]) % size + 1) % size;
			if (&tab[lig][col]) /* case occupée */
				lig = (lig - 1);

			pTab = &tab[lig][col];
		}

		*pTab = i;
	}

	for (pTab = &tab[0][0]; pTab < &tab[0][0] + size * size; pTab++)
	{
		printf("%d\t", *pTab);

		if ((pTab - &tab[0][0]) % size == size - 1)
			printf("\n");
	}


	return 0;
}
