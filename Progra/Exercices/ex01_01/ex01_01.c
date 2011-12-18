#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int a,b;

	printf("Entrez un premier entier: ");
	scanf("%d", &a);

	printf("Entrez un second entier: ");
	scanf("%d", &b);

	printf("La somme de %d et %d est %d\n",
		a, b,
		a + b);

	return 0;
}