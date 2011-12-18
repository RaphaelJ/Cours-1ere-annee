#include <stdio.h>

#define MAX_ELEMENTS 30

void show_array(int *array, int size); /* Affiche un tableau */

int main (void)
{
	int n,
		k = -1, /* Première valeur non nulle */
		va[MAX_ELEMENTS], *pVa;

	printf("Combien d'elements souhaitez-vous encoder (1~%d) : ",
		MAX_ELEMENTS);
	scanf("%d", &n);

	if (n < 1)
		n = 1;
	else if (n > MAX_ELEMENTS)
		n = MAX_ELEMENTS;

	for (pVa = va; pVa < va + n; pVa++)
	{
		scanf("%d", pVa);
		
		if (k < 0 && *pVa != 0)
			k = 1;
	}

	show_array(va, n);

	printf("K = %d\n", k);
}

void show_array(int *array, int size) /* Affiche un tableau */
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%5d", *array);
		array++;
	}
	printf("\n");
}