#include <stdio.h>

int main (void)
{
	int selection;

	printf("Quel temps fait-il dehors ?\n");
	printf("1. Ensoleille\n");
	printf("2. Pluvieux\n");
	printf("3. Gris\n");
	printf("4. Neige\n");

	printf("Votre choix: ");
	scanf("%d", &selection);

	switch (selection)
	{
	case 1: 
		printf("Promenons nous dans les bois !\n");
		break;
	case 2:
		printf("Allons voir le nouveau James Bond !\n");
		break;
	case 3:
		printf("On peut aller a la piscine couverte ?\n");
		break;
	case 4:
		printf("On peut sortir la luge et aller en faire sur le toit de la gare ?\n");
		break;
	default:
		printf("Pourquoi ne pas en profiter pour lire la bible ?\n");
	}

	return 0;
}
