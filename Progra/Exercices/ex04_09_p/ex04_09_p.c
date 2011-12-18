#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

int r_rand(int min, int max);

int main (void) 
{
	int Vect[ARRAY_SIZE], *pVect,
		VectRepeat[11] = {0}, *pVectRepeat;

	srand(time(NULL));

	printf("Vecteur :\n");

	pVectRepeat = VectRepeat;

	for (pVect = Vect; pVect <= Vect + ARRAY_SIZE; pVect++)
	{
		*pVect = r_rand(0, 10);

		++*(pVectRepeat + *pVect);

		printf("%d\t", *pVect);
	}
	printf("\n");

	printf("Repetitions :\n");
	for (; pVectRepeat <= VectRepeat + 10; pVectRepeat++)
	{
		printf("%d: %d\t",
			pVectRepeat - VectRepeat,
			*pVectRepeat);
	}
}

int r_rand(int min, int max) /* Retoure un nombre aléatoire compris entre min et max (inclus) */
{
	return (int) (rand() % (max - min +  1) + min);
}