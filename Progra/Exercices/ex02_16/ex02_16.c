#include <stdio.h>

int main (void)
{
	int x, y;
	char partie;
	
	printf("Entrez les coordonnees d'un point:\n");

	printf("x: ");
	scanf("%d", &x);

	printf("y: ");
	scanf("%d", &y);

	if (x > 0) /* Droite */
	{
		if (y > 0) /* Suppérieur droit */
			partie = 1;
		else if (y < 0) /* Inférieur droit */
			partie = 7;
		else /* Milieu droit */
			partie = 8;
	}
	else if (x < 0) /* Gauche */
	{
		if (y > 0) /* Suppérieur gauche */
			partie = 3;
		else if (y < 0) /* Inférieur gauche */
			partie = 5;
		else /* Milieu gauche */
			partie = 4;
	}
	else /* Milieu */
	{
		if (y > 0) /* Milieu suppérieur */
			partie = 2;
		else if (y < 0) /* Milieu inférieur */
			partie = 6;
		else /* Centre */
			partie = 9;
	}

	printf("Le point (%d, %d) se trouve dans la partie %d du plan.\n",
		x, y, partie);
}
