#include <stdio.h>
#include <stdlib.h>

int Add(int nb1, int nb2);
int Diff(int nb1, int nb2);
int Mult(int nb1, int nb2);
int Div(int nb1, int nb2);
int Mod(int nb1, int nb2);
int main (void)
{
	int valeur1, valeur2, resultat;
	char operateur;

	printf("Premier nombre: ");
	scanf("%d", &valeur1);

	do {
		printf("Operateur: ");
		scanf("%c", &operateur);
	} while(operateur != '+'
		&& operateur != '-'
		&& operateur != '*'
		&& operateur != '/'
		&& operateur != '%');

    printf("Premier nombre: ");
	scanf("%d", &valeur2);
	
	switch (operateur)
	{
	case '+':
		resultat = Add(valeur1, valeur2);
		break;
	case '-':
		resultat = Diff(valeur1, valeur2);
		break;
	case '*':
		resultat = Mult(valeur1, valeur2);
		break;
	case '/':
		resultat = Div(valeur1, valeur2);
		break;
	case '%':
		resultat = Mod(valeur1, valeur2);
	}

	printf("%d %c %d = %d\n",
		valeur1, operateur, valeur2, resultat);
}

int Add(int nb1, int nb2)
{
	return nb1 + nb2;
}
int Diff(int nb1, int nb2)
{
	return nb1 - nb2;
}
int Mult(int nb1, int nb2)
{
	return nb1 * nb2;
}
int Div(int nb1, int nb2)
{
	return nb1 / nb2;
}
int Mod(int nb1, int nb2)
{
	return nb1 % nb2;
}
