#include <stdio.h>
#include <math.h>

#define SHORT_MINVALUE  (short) - pow(2, 15)
#define SHORT_MAXVALUE (short) (pow(2, 15) - 1)

int main (void)
{
	int valeur;
	short valeur_short;


	do {
		printf("Entrez une valeur entiere (min: %d - max: %d): ",
			SHORT_MINVALUE, SHORT_MAXVALUE);
		scanf("%d", &valeur);
	} while ((valeur_short = (short) valeur) != valeur);

	printf("Valeur acceptee\n");
}
