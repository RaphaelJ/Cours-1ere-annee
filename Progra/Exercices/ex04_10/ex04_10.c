#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

int r_rand(int min, int max);

int main (void) 
{
	int Vect[ARRAY_SIZE], i,
		lastVal = 11, currSequStart = -1,
		maxSequence[2] = { 0, 0 }; /* { NbRepetition, Start } */

	srand(time(NULL));

	printf("Vecteur :\n");

	for (i = 0; i < ARRAY_SIZE; i++)
	{
		Vect[i] = r_rand(0, 10);

		printf("%d\t", Vect[i]);

		if (lastVal >= Vect[i]) /* R‡Z */
		{
			currSequStart = i;
		}

		lastVal = Vect[i];

		if (maxSequence[0] < (i - currSequStart) + 1)
		{
			maxSequence[0] = (i - currSequStart) + 1;
			maxSequence[1] = currSequStart;
		}

	}
	printf("\n");

	printf("La plus longue sequence en ordre croissant est "
		"de %d et commence a l'index %d\n",
		maxSequence[0], maxSequence[1]);

	for (i = maxSequence[1]; i < maxSequence[1] + maxSequence[0]; i++)
	{
		printf("%d\t", Vect[i]);
	}
	printf("\n");
}

int r_rand(int min, int max) /* Retoure un nombre alÈatoire compris entre min et max (inclus) */
{
	return (int) (rand() % (max - min +  1) + min);
}