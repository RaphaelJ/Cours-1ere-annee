#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bool char
#define true 1
#define false 0

#define byte char

#define SIZE 10

int main(void)
{
	byte Tab[SIZE][SIZE],
		nbLgn, nbCol;
	
	srand(time(NULL));
	init_tab(Tab, &nbLgn, &nbCol);

	return 0;
}

int init_tab(byte *Tab, &nbLgn, &nbCol)
{
	byte lgn, col, *pTab;

	do {
		printf("Nombre de lignes: ");
		scanf("%d", nbLgn);
	} while (*nbLgn > SIZE || *nbLgn <= 0);

	do {
		printf("Nombre de colonnes: ");
		scanf("%d", nbCol);
	} while (*nbCol > SIZE || *nbCol <= 0);

	for (lgn = 0; lgn < nbLgn; lgn++) {
		pTab = Tab + lgn * nbLgn;

		for (col = 0; col < nbCol; col++) {
			*pTab = rand() % 2 + 1;

			pTab++;
		}
	}
}
