#include <stdio.h>

int main (void)
{
	int selection;

	printf("Quel temps fait-il dehors ?\n");
	printf("1. Ensoleille\n");
	printf("2. Pluvieux\n");

	printf("Votre choix: ");
	scanf("%d", &selection);

	if (selection == 1)
	{
		printf("Promenons nous dans les bois !\n");
	}
	else
	{
		printf("Allons voir le nouveau James Bond !\n");
	}

	return 0;
}
