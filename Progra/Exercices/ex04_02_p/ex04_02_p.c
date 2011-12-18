#include <stdio.h>

#define MAX_ELEMENTS 30

void show_array(int *array, int size); /* Affiche un tableau */

int main (void)
{
	int n,
		avg = 0,
		va[MAX_ELEMENTS], *pVa,
		vb[MAX_ELEMENTS], *pVb;

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

		avg += *pVa;
	}
	avg /= n;

	for (pVa = va, pVb = vb; pVa < va + n; pVa++, pVb++)
		*pVb = *pVa - avg;

	show_array(&va[0], n);

	printf("Moyenne: %d\n",
		avg);

	printf("Ecart:\n");
	show_array(&vb[0], n);
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