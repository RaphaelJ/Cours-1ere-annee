#include <stdio.h>

int main (void)
{
	int age, sexe;

	printf("Quel est votre age: ");
	scanf("%d", &age);

	printf("Etes-vous un homme (1) ou une femme (2): ");
	scanf("%d", &sexe);

	if (age < 10)
	{
		if (sexe == 1)
			printf("Salut petit\n");
		else 
			printf("Salut petite\n");
	}
	else if (age < 18) 
	{
		if (sexe == 1)
			printf("Salut mec !\n");
		else
			printf("Salut miss !\n");
	}
	else
	{
		if (sexe == 1)
			printf("Bonjour monsieur\n");
		else
			printf("Bonjour madamme\n");
	}

}