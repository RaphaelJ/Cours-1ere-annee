#include <stdio.h>

int main (void)
{
	int selection;

	printf("Quel temps fait-il dehors ?\n");
	printf("1. Ensoleille\n");
	printf("2. Pluvieux\n");
	printf("3. Gris\n");

	printf("Votre choix: ");
	scanf("%d", &selection);

	if (selection == 1)
	{
		printf("Promenons nous dans les bois !\n");
	}
	else if (selection == 2)
	{
		printf("Allons voir le nouveau James Bond !\n");
	}
	else
	{
		printf("On peut aller a la piscine couverte ?\n");
	}

	return 0;
}