#include <stdio.h>

int main (void) 
{
	int cible,
		index = -1,
		left = 0,
		right = 50, /* = longeur du tableau */
		tab[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
			11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
			21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
			31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
			41, 42, 43, 44, 45, 46, 47, 48, 49, 50 },
		ImL, /* I'm Lucky ! */
		nbIterations = 0;

	printf("Quelle valeur souhaitez-vous rechercher : ");
	scanf("%d", &cible);

	while (index < 0 && left < right)
	{
		nbIterations++;

		if ((right - left) > 1)
		{
			ImL = left + (right - left) / 2;

			if (tab[ImL] == cible)
				index = ImL;
			else if (tab[ImL] < cible)
				left = ImL;
			else
				right = ImL;
		}
		else /* Dernière possibilité */
		{
			if (tab[left] == cible)
				index = left;
			break;
		}
	}

	/* Prends la première occurence */
	while (index > 0 && tab[index - 1] == cible)
		index--;

	printf("La cible se trouve a l'index %d\n"
		"%d iteration(s) necessaire(s)\n",
		index, nbIterations);
}