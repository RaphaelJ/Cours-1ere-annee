#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) 
{
	int cote_1, cote_2;

	printf("Premier cote (hors hypothenuse) du triangle rectangle: ");
	scanf("%d", &cote_1);
	
	printf("Deuxieme cote du triangle rectangle: ");
	scanf("%d", &cote_2);

	printf("L'hypotenuse de ce triangle est %.2f\n",
		sqrt(pow(cote_1, 2) + pow(cote_2, 2))); /* Hypothenuse du triangle */

	return 0;
}
