#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_PRENOMS 3
#define MAX_PRENOMS 20

#define MAX_SIZE 50

typedef unsigned char bool;
#define true 1
#define false 0

void getPrenoms(char prenoms[MAX_PRENOMS][MAX_SIZE], char nbPrenoms)
{
	for ( ; nbPrenoms > 0; nbPrenoms--, prenoms++)
		scanf("%sMAX_SIZE", &prenoms[0]);
}

void trierPrenoms(char prenoms[MAX_PRENOMS][MAX_SIZE], char nbPrenoms)
{
        int trie, i;
	char tmp[MAX_SIZE];

        for (trie = 1; trie < nbPrenoms; trie++) {
                strcpy(tmp, prenoms[trie]);
                i = trie - 1;
                for (i = trie - 1; i >= 0 && strcmp(tmp, prenoms[i]) < 0; i--) {
                        strcpy(prenoms[i + 1], prenoms[i]);
                }
                strcpy(prenoms[i + 1], tmp);
        }

}

int searchPrenom(char prenoms[MAX_PRENOMS][MAX_SIZE], char nbPrenoms, char prenom[MAX_PRENOMS])
{
	char left = 0,
	     right = nbPrenoms - 1,
	     milieu;
	
	while (left <= right) {
		milieu = (left + right) / 2;
		if (strcmp(prenom, prenoms[milieu]) < 0)
			right = milieu - 1;
		else
			left = milieu + 1;
	}

	if (strcmp(prenoms[left - 1], prenom) != 0)
		return -1;
	else
		return left;
}

int main(void) 
{
	char prenoms[MAX_PRENOMS][MAX_SIZE], prenom[MAX_SIZE];
	char nbPrenoms = 0;

	printf("Nombre de prenoms : ");
	scanf("%d", &nbPrenoms);

	getPrenoms(prenoms, nbPrenoms);
	trierPrenoms(prenoms, nbPrenoms);

	printf("Prenom a rechercher: ");
	scanf("%s", prenom);

	printf("Indice : %d", 
		searchPrenom(prenoms, nbPrenoms, prenom));

	return 0;
}
