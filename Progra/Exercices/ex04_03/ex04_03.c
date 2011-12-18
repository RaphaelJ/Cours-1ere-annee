#include <stdio.h>

#define MAX_ELEMENTS 30

void show_array(int *array, int size); /* Affiche un tableau */

int main (void)
{
	int n,
		i,
		va[MAX_ELEMENTS];

	printf("Combien d'elements souhaitez-vous encoder (3~%d) : ",
		MAX_ELEMENTS);
	scanf("%d", &n);

	if (n < 3)
		n = 3;
	else if (n > MAX_ELEMENTS)
		n = MAX_ELEMENTS;

	for (i = 0; i < 2; i++)
		scanf("%d", &va[i]);

	for (i = 2; i < n; i++)
		va[i] = va[i - 1] * va[i - 2];

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