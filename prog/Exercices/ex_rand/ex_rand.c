#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int r_rand(int min, int max) /* Retoure un nombre aléatoire compris entre min et max (inclus) */
{
	return (int) (rand() % (max - min +  1) + min);
}

int main (void) 
{
	short x;

	srand((unsigned) time(NULL));

	x = rand() % 11;

	/*printf("%hd\n", x);*/
	printf("%d", r_rand(0, 1));
}
