#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBPRENOMS 4
#define MAXPRENOMSIZE 10


void lire_prenom(char *prenom);
void inserer_prenoms(char prenoms[NBPRENOMS][MAXPRENOMSIZE], int nbPrenoms);
void trier_prenoms(char prenoms[NBPRENOMS][MAXPRENOMSIZE], int nbPrenoms);
void afficher_prenoms(char prenoms[NBPRENOMS][MAXPRENOMSIZE], int nbPrenoms);

int main(void)
{
	char prenoms[NBPRENOMS][MAXPRENOMSIZE];
	int nbPrenoms;

	do {
		printf("Nombre de prenoms : ");
		scanf("%d", &nbPrenoms);
	} while (nbPrenoms < 1 || nbPrenoms > NBPRENOMS); 
	getchar();

	inserer_prenoms(prenoms, nbPrenoms);
	trier_prenoms(prenoms, nbPrenoms);
	
	printf("\nPrenoms tries :\n");
	afficher_prenoms(prenoms, nbPrenoms);
}

void lire_prenom(char prenom[MAXPRENOMSIZE]) 
{
	int len = 0;
	char c;

	while (len < MAXPRENOMSIZE && (c = getchar()) != '\n') {
		prenom[len] = c;
		len++;
	}
	prenom[len] = '\0';
}

void inserer_prenoms(char prenoms[NBPRENOMS][MAXPRENOMSIZE], int nbPrenoms) 
{
	int index;
	for (index = 0; index < nbPrenoms; index++)
		lire_prenom(prenoms[index]);
}

void trier_prenoms(char prenoms[NBPRENOMS][MAXPRENOMSIZE], int nbPrenoms)
{
	int trie, i;
	char tmp[MAXPRENOMSIZE];

	for (trie = 1; trie < nbPrenoms; trie++) {
		strcpy(tmp, prenoms[trie]);
		i = trie - 1;
		for (i = trie - 1; i >= 0 && strcmp(tmp, prenoms[i]) < 0; i--) {
			strcpy(prenoms[i + 1], prenoms[i]);
		}
		strcpy(prenoms[i + 1], tmp);
	}

}

void afficher_prenoms(char prenoms[NBPRENOMS][MAXPRENOMSIZE], int nbPrenoms)
{
	int index;
	for (index = 0; index < nbPrenoms; index++)
		printf("%s\n", prenoms[index]);
}


