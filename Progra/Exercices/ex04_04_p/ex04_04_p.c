#include <stdio.h>

#define MAX_ELEMENTS 30

void show_array(float *array, int size); /* Affiche un tableau */

int main (void)
{
	int n;
	
	float tmp,
		va[MAX_ELEMENTS], *pVa, *pVaB;

	printf("Combien d'elements souhaitez-vous encoder (1~%d) : ",
		MAX_ELEMENTS);
	scanf("%d", &n);

	if (n < 1)
		n = 1;
	else if (n > MAX_ELEMENTS)
		n = MAX_ELEMENTS;

	for (pVa = va; pVa < va + n; pVa++)
		scanf("%f", pVa);

	for (pVa = va, pVaB = va + n - 1; pVa < va + (n / 2 + n % 2); pVa++, pVaB--) 
	{
		tmp = *pVa;
		*pVa = 1 / *pVaB;
		*pVaB = 1 / tmp;
	}

	show_array(&va[0], n);
}

void show_array(float *array, int size) /* Affiche un tableau */
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%5.2f", *array);
		array++;
	}
	printf("\n");
}