#include <stdio.h>

#define SEARCH_MAX 500

void afficher_somme(int *array, int size); /* Affiche la somme des éléments d'un tableau */

int main (void) 
{
	int i = 0,
		i_div,
		num_div,
		list_div[50],
		moitie,
		somme_div;

	printf("== Nombres parfaits (inferieurs ou egaux a %d) ==\n",
		SEARCH_MAX);

	while (i++ < 500)
	{
		moitie = i / 2;
		num_div = 0;
		i_div = 0;
		somme_div = 0;

		while (i_div++ < moitie)
		{
			if (i % i_div == 0)
			{
				list_div[num_div++] = i_div;
				somme_div += i_div;
			}
		}

		if (somme_div == i) /* Nbre parfait */
		{
			printf("%4d = ", i);

			afficher_somme(list_div, num_div);
			printf("\n");
		}
	}
}

void afficher_somme(int *array, int size) /* Affiche la somme des éléments d'un tableau */
{
	int i;

	for (i = 0; i < size; i++)
	{	
		printf("%d",
			*array);

		if (i + 1 != size)
			printf(" + ");

		array++;
	}
}
