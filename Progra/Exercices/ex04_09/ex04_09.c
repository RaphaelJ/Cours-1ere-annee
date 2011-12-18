#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

int r_rand(int min, int max);

int main (void) 
{
	int Vect[ARRAY_SIZE], i,
		VectRepeat[11] = {0};

	srand(time(NULL));

	printf("Vecteur :\n");

	for (i = 0; i < ARRAY_SIZE; i++)
	{
		Vect[i] = r_rand(0, 10);

		VectRepeat[Vect[i]]++;

		printf("%d\t", Vect[i]);
	}
	printf("\n");

	printf("Repetitions :\n");
	for (i = 0; i <= 10; i++)
	{
		printf("%d: %d\t", i, VectRepeat[i]);
	}
}

int r_rand(int min, int max) /* Retoure un nombre aléatoire compris entre min et max (inclus) */
{
	return (int) (rand() % (max - min +  1) + min);
}