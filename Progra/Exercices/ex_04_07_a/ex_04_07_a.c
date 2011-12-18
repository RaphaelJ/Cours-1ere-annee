#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE 30

int r_rand(int min, int max);

int main (void)
{
	int	nbL, nbC, lgn, col, curr,
		max_repeat[4] = { 0 },/* 0 : valeur - 1 : repetition - 2 : ligne - 3 : col */
		curr_repeat[4] = { 0 };

	printf("Combien de lignes souhaitez-vous pour votre tableau : ");
	scanf("%d", &nbL);

	printf("Combien de colonnes souhaitez-vous pour votre tableau : ");
	scanf("%d", &nbC);

	srand(time(NULL));

	for (lgn = 0; lgn < nbL; lgn++)
	{
		for (col = 0; col < nbC; col++)
		{
			curr = r_rand(1, 3);
			printf("%d\t", curr);

			if (curr_repeat[0] != curr)
			{
				curr_repeat[0] = curr;
				curr_repeat[1] = 1;
				curr_repeat[2] = lgn;
				curr_repeat[3] = col;
			}
			else
				curr_repeat[1]++;

			if (curr_repeat[1] > max_repeat[1])
			{
				/* max_repeat = curr_repeat; Erreur */
				max_repeat[0] = curr_repeat[0];
				max_repeat[1] = curr_repeat[1];
				max_repeat[2] = curr_repeat[2];
				max_repeat[3] = curr_repeat[3];
			}
		}
		curr_repeat[0] = 0; // Remet à zero le compteur pour chaque ligne
		printf("\n");
	}

	printf("La valeur %d se repete %d fois "
		"et commence a la ligne %d et a la colonne %d\n",
		max_repeat[0], max_repeat[1],
		max_repeat[2], max_repeat[3]);
}

int r_rand(int min, int max) /* Retoure un nombre aléatoire compris entre min et max (inclus) */
{
	return (int) (rand() % (max - min +  1) + min);
}