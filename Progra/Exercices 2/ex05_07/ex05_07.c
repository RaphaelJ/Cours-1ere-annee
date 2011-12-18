#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15

int InitVect(short *Vect);
void ShowVect(short *Vect, int Size);

int main (void)
{
	short Vect[SIZE],
		Tab[SIZE][SIZE];
	int nbCol, nbLgn;
	
	srand(time(NULL));

	nbCol = InitVect(Vect);
	ShowVect(Vect, nbCol);

	return 0;
}

int InitVect(short *Vect)
{
	int Size, i;

	do {
		printf("Taille du vecteur : ");
		scanf("%d", &Size);
	} while (Size > SIZE || Size < 2);

	for (i = 0; i < Size; i++)
		*(Vect++) = rand() % 11 - 5;

	return Size;
}

void ShowVect(short *Vect, int Size)
{
	int i;
	for (i = 0; i < Size; i++, Vect++)
		printf("%d\t", *Vect);
}

void TrierVect(short *Vect, int Size)
{
	
}