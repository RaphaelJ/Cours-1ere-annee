#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void initVect(int *iVect, short *sVect);
void afficherVect(int *iVect, short *sVect);

int main (void)
{
	int iVect[SIZE];
	short sVect[SIZE];

	srand(time(NULL));

	initVect(iVect, sVect);
	afficherVect(iVect, sVect);
}

void initVect(int *iVect, short *sVect)
{
	int i;
	for (i = 0; i < SIZE; i++, iVect++, sVect++)
		*iVect = *sVect = rand();
}

void afficherVect(int *iVect, short *sVect)
{
	int i;
	for (i = 0; i < SIZE; i++, iVect++)
		printf("%d: %d\t", iVect, *iVect);

	printf("\n");

	for (i = 0; i < SIZE; i++, sVect++)
		printf("%d: %d\t", sVect, *sVect);
}