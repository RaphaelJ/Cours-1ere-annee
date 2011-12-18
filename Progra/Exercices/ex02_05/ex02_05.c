#include <stdio.h>

#define CHANGE_EURO_DOLLARD 1.47

int main (void) 
{
	short choix;
	float origine;

	printf("Quel type de convertion souhaitez vous faire ?\n");
	printf("1. Euro -> Dollard\n");
	printf("2. Dollard -> Euro\n");
	
	printf("Votre choix: ");
	scanf("%d", &choix);

	printf("Devise d'origine: ");
	scanf("%f", &origine);

	if (choix == 1)
	{
		printf("%4.2f euro = %4.2f dollard\n",
			origine,
			origine * CHANGE_EURO_DOLLARD);
	}
	else
	{
		printf("%4.2f dollard = %4.2f euro\n",
			origine,
			origine / CHANGE_EURO_DOLLARD);
	}

	return 0;
}
