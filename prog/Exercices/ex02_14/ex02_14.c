#include <stdio.h>

int main (void) 
{
	float nb1, nb2, resultat;
	char operateur;

	printf("Entrez un premier nombre: ");
	scanf("%f", &nb1);

	printf("Entrez un second nombre: ");
	scanf("%f", &nb2);

	fflush(stdin);

	printf("Entrez un operateur (+, -, *, / ou %): ");
	scanf("%c", &operateur);

	switch (operateur)
	{
	case '+':
		resultat = nb1 + nb2;
		break;
	case '-':
		resultat = nb1 - nb2;
		break;
	case '*':
		resultat = nb1 * nb2;
		break;
	case '/':
		resultat = nb1 / nb2;
		break;
	case '%':
		resultat = (float) ((int) nb1 % (int) nb2);
		break;
	}

	printf("%.2f %c %.2f = %.2f\n",
		nb1,
		operateur,
		nb2,
		resultat);

	return 0;
}