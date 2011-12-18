#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15

int InitVect(short *Vect);
void ShowVect(short *Vect, int Size);

Déclarer un tableau à deux dimensions. Demander le nombre de lignes et de colonnes que
l'utilisateur veut réellement utiliser (une seule valeur à demander : on souhaite un tableau carré,
le nombre de lignes est donc égal au nombre de colonnes).  
Écrire  et appeler une fonction qui initialisera le tableau avec des valeurs comprises entre 1 et 100.
Afficher le tableau.
Calculer dans une fonction et afficher dans la fonction main la trace
(somme des éléments de la première diagonale) du tableau carré.
int main (void)
{
	short Tab[SIZE][SIZE];

	

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