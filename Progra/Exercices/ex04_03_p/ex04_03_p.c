#include <stdio.h>

#define MAX_ELEMENTS 30

void show_array(int *array, int size); /* Affiche un tableau */

int main (void)
{
	int n,
		va[MAX_ELEMENTS], *pVa;

	printf("Combien d'elements souhaitez-vous encoder (3~%d) : ",
		MAX_ELEMENTS);
	scanf("%d", &n);

	if (n < 3)
		n = 3;
	else if (n > MAX_ELEMENTS)
		n = MAX_ELEMENTS;

	for (pVa = va; pVa < va + 2; pVa++)
		scanf("%d", pVa);

	for (pVa = va + 2; pVa < va + n; pVa++)
		*pVa = *(pVa - 1) * *(pVa - 2);

	show_array(&va[0], n);
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