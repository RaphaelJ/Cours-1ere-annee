#include <stdio.h>

#define MAX_ELEMENTS 30

void show_array(int *array, int size); /* Affiche un tableau */

int main (void)
{
	int n,
		i,
		k = -1,
		va[MAX_ELEMENTS];

	printf("Combien d'elements souhaitez-vous encoder (1~%d) : ",
		MAX_ELEMENTS);
	scanf("%d", &n);

	if (n < 1)
		n = 1;
	else if (n > MAX_ELEMENTS)
		n = MAX_ELEMENTS;

	for (i = 0; i < n; i++)
	{
		scanf("%d", &va[i]);
		
		if (k < 0 && va[i] != 0)
			k = 1;
	}

	show_array(&va[0], n);

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