#include <stdio.h>

#define MAX_ELEMENTS 30

void show_array(float *array, int size); /* Affiche un tableau */

int main (void)
{
	int n,
		i;
	
	float tmp,
		va[MAX_ELEMENTS];

	printf("Combien d'elements souhaitez-vous encoder (1~%d) : ",
		MAX_ELEMENTS);
	scanf("%d", &n);

	if (n < 1)
		n = 1;
	else if (n > MAX_ELEMENTS)
		n = MAX_ELEMENTS;

	for (i = 0; i < n; i++)
		scanf("%f", &va[i]);

	for (i = 0; i < n / 2 + n % 2; i++)
	{
		tmp = va[i];
		va[i] = 1 / va[n - 1 - i];
		va[n - 1 - i] = 1 / tmp;
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