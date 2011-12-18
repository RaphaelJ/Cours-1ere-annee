#include <stdio.h>

int main(void)
{
	float nb1, nb2, nb3, nb4;

	printf("Entrez un premier nombre: ");
	scanf("%f", &nb1);

	printf("Un deuxieme nombre: ");
	scanf("%f", &nb2);

	printf("Un troisieme nombre: ");
	scanf("%f", &nb3);

	printf("Et un quatrieme nombre: ");
	scanf("%f", &nb4);

	printf("%15.2f\n", nb1);
	printf("%15.2f\n", nb2);
	printf("%15.2f\n", nb3);
	printf("+%14.2f\n", nb4);
	printf("---------------\n");
	printf("%15.2f\n",
		nb1 + nb2 + nb3 + nb4);
}
