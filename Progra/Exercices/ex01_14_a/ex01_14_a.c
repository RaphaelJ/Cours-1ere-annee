#include <stdio.h>

int main(void)
{
	int nb1, nb2, nb3, nb4, somme;

	printf("Entrez un premier nombre: ");
	scanf("%d", &nb1);

	printf("Entrez un deuxieme nombre: ");
	scanf("%d", &nb2);

	printf("Entrez un troisieme nombre: ");
	scanf("%d", &nb3);

	printf("Entrez un quatrieme nombre: ");
	scanf("%d", &nb4);

	somme = nb1 + nb2 + nb3 + nb4;

	printf("La somme de ces nombres est %d\n", somme);

	return 0;
}