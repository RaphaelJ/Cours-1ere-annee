#include <stdio.h>

int main(void)
{
	int nombre, somme;

	printf("Entrez un premier nombre: ");
	scanf("%d", &nombre);
	somme = nombre;

	printf("Entrez un deuxieme nombre: ");
	scanf("%d", &nombre);
	somme += nombre;

	printf("Entrez un troisieme nombre: ");
	scanf("%d", &nombre);
	somme += nombre;

	printf("Entrez un quatrieme nombre: ");
	scanf("%d", &nombre);
	somme += nombre;

	printf("La somme de ces nombres est %d\n", somme);

	return 0;
}