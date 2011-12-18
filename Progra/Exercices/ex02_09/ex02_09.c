#include <stdio.h>

#define PI 3.141516

int main (void)
{
	int forme, superficie, perimetre,
		cote1, cote2, cote3, hauteur, rayon;

	printf("Quel forme souhaitez-vous utiliser: \n");
	printf("1. Carre\n");
	printf("2. Rectangle\n");
	printf("3. Losange\n");
	printf("4. Parallelogramme\n");
	printf("5. Trapeze\n");
	printf("6. Triangle\n");
	printf("7. Cercle\n");
	scanf("%d", &forme);

	switch (forme)
	{
	case 1: /* Carré */
		printf("Longueur du cote du carre: ");
		scanf("%d", &cote1);

		superficie = cote1 * cote1;
		perimetre = 4 * cote1;
	case 2: /* Rectangle */
		printf("Longueur du premier cote: ");
		scanf("%d", &cote1);

		printf("Longueur du second cote: ");
		scanf("%d", &cote2);

		superficie = cote1 * cote2;
		perimetre = cote1 * 2 + cote2 * 2;
	case 3: /* Losange */
		printf("Grande diagonale: ");
		scanf("%d", &base);

		printf("Petite diagonale: ");
		scanf("%d", &hauteur);

		superficie = base * hauteur;
		perimetre = sqrt(base * base + hauteur * hauteur) / 2; /* A verifier */

	case 4: /* Parallelogramme */ 
		printf("Longueur du grand cote: ");
		scanf("%d", &cote1);

		printf("Longueur du petit cote: ");
		scanf("%d", &cote2);

		printf("Hauteur: ");
		scanf("%d", &hauteur);

		superficie = hauteur * grand_cote;
		perimetre = (petit_cote + grand_cote) * 2;
	case 5: /* Trapeze */ 
		printf("Longueur du grand cote: ");
		scanf("%d", &cote1);

		printf("Longueur du petit cote: ");
		scanf("%d", &cote2);

		printf("Hauteur: ");
		scanf("%d", &hauteur);

		superficie = (int) (hauteur * (cote1 + cote2)) / 2.0;
		perimetre = cote1 * 2 + cote2 * 2; /* A verifier */
	case 6: /* Triangle */
		printf("Base: ");
		scanf("%d", &cote1);

		printf("Deuxieme cote: ");
		scanf("%d", &cote2);

		printf("Troisieme cote: ");
		scanf("%d", &cote3);

		printf("Hauteur: ");
		scanf("%d", &hauteur);

		superficie = (base * hauteur) / 2;
		perimetre = cote1 + cote2 + cote3;
	case 7: /* Cercle */
		printf("Rayon: ");
		scanf("%d", &rayon);

		superficie = PI * (rayon * rayon);
		perimetre = 2 * PI * rayon;
	default:
		printf("Valeur incorrecte");
		return 1;
	}

	printf("Aire de la forme: %d",
		superficie);
	printf("Perimetre de la forme: %d",
		perimetre);

	return 0;
}