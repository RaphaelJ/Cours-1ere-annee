#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initVect(char *vect, short nb);
void afficherVect(char *vect, short nb);
void compter(char *vect, char *compteur, short nb);
void afficherCompteur(char *compteur);

int main (void)
{
	char v[50], vcpt[10] = { 0 },
		size;

	srand(time(NULL));

	do {
		printf("Taille du tableau: ");
		scanf("%d", &size);
	} while (size < 1 || size > 50);

	initVect(v, size);
	afficherVect(v, size);

	compter(v, vcpt, size);
	afficherCompteur(vcpt);
}
	

void initVect(char *vect, short nb)
{
	int i;
	for (i = 0; i < nb; i++, vect++)
		*vect = rand() % 10 + 1;
}

void afficherVect(char *vect, short nb)
{
	int i;
	for (i = 0; i < nb; i++, vect++)
		printf("%d\t", *vect);
	printf("\n");
}

void compter(char *vect, char *compteur, short nb)
{
	int i;
	for (i = 0; i < nb; i++, vect++)
		(*(compteur + *vect - 1))++;
}
void afficherCompteur(char *compteur)
{
	int i;
	for (i = 1; i <= 10; i++, compteur++)
		printf("%d: %d\n", i, *compteur);
}