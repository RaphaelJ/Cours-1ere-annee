#include <stdio.h>

/* Donne le PGCD de deux nombres */
int pgcd (int nb1, int nb2);

int main (void)
{
	int nb1, nb2;
	
	printf("Entrez un premier nombre: ");
	scanf("%d", &nb1);

	printf("Entrez un second nombre: ");
	scanf("%d", &nb2);

	printf("Le plus grand PGCD entre ces deux nombres est %d\n",
		pgcd(nb1, nb2));
}

/* Donne le PGCD de deux nombres */
int pgcd (int nb1, int nb2) 
{
	while (nb1 != nb2)
	{
		if (nb1 > nb2)
			nb1 -= nb2;
		else
			nb2 -= nb1;
	}

	return nb1;
}