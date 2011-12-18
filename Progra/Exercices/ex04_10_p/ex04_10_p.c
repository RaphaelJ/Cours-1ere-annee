#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

int r_rand(int min, int max);

int main (void) 
{
	int Vect[ARRAY_SIZE], *pVect,
		lastVal = 11, currSequStart = -1,
		maxSequence[2] = { 0, 0 }; /* { NbRepetition, Start } */

	srand(time(NULL));

	printf("Vecteur :\n");

	for (pVect = Vect; pVect < Vect + ARRAY_SIZE; pVect++)
	{
		*pVect = r_rand(0, 10);

		printf("%d\t", *pVect);

		if (lastVal >= *pVect) /* R‡Z */
		{
			currSequStart = pVect - Vect;
		}

		lastVal = *pVect;

		if (*maxSequence < ((pVect - Vect) - currSequStart) + 1)
		{
			*maxSequence = ((pVect - Vect) - currSequStart) + 1;
			*(maxSequence + 1) = currSequStart;
		}

	}
	printf("\n");

	printf("La plus longue sequence en ordre croissant est "
		"de %d et commence a l'index %d\n",
		maxSequence[0], maxSequence[1]);

	for (pVect = Vect + maxSequence[1]; pVect <  Vect + maxSequence[1] + maxSequence[0]; pVect++)
	{
		printf("%d\t", *pVect);
	}
	printf("\n");
}

int r_rand(int min, int max) /* Retoure un nombre alÈatoire compris entre min et max (inclus) */
{
	return (int) (rand() % (max - min +  1) + min);
}