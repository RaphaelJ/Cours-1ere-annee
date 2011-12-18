#include <stdio.h>

int main (void) 
{
	char restart, table, col, ligne;

	do {
		printf("Quel table souhaitez-vous afficher (1~20): ");
		scanf("%d", &table);

		if (table > 20)
			table = 20;
		else if (table < 1)
			table = 1;

		for (ligne = 0; ligne <= table; ligne++)
		{
			if (ligne > 0) /* On affiche pas le numero 0 pour la ligne d'en tête */
				printf("%4d", ligne);
			else 
				printf("    ");

			for (col = 1; col <= table; col++)
			{
				if (ligne > 0)
					printf("%4d",
						col * ligne);
				else /* En tête */
					printf("%4d",
						col * 1);
			}

			printf("\n");
		}

		printf("Continuer (0: Non - 1: Oui) : ");
		scanf("%d", &restart);
	} while (restart);


}