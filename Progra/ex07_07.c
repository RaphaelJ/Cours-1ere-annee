#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define NOM_LONG 25
#define DIM 5

typedef char bit;

typedef struct _DATE {
	short jour;
	short mois;
	short annee;
} DATE;

typedef struct _PERS {
	short id;	

	char prenom[NOM_LONG];
	char nom[NOM_LONG];
	
	DATE naissance;
} PERS;

typedef struct _INDEX {
	char nom[NOM_LONG];
	
	short adresse;
} INDEX;

int IndexComparator(const void * elem1, const void * elem2)
{
	return strcmp(((INDEX*) elem1)->nom, ((INDEX*) elem2)->nom);
}

void InitIndex(const PERS perso[DIM], INDEX * index)
{
	short i;
	
	for (i = 0; i < DIM; i++) {
		strcpy(index[i].nom, perso[i].nom);
		index[i].adresse = i;
	}

	qsort(index, DIM, sizeof(INDEX), IndexComparator);
}

void PrintPers(const PERS pers)
{
	printf("%hd\t%s\t%s\t%hd/%hd/%hd\n",
		pers.id, pers.nom, pers.prenom,
		pers.naissance.jour, pers.naissance.mois,
			pers.naissance.annee);
}
void Liste(const PERS perso[DIM], const bit occup[DIM],
	const INDEX index[DIM])
{
	short i;

	for (i = 0; i < DIM; i++) {
		if (occup[i])
			PrintPers(perso[index[i].adresse]);
	}
}

void Recherche(const PERS perso[DIM], const bit occup[DIM],
	const INDEX index[DIM],	const char nom[NOM_LONG])
{
	short i;
	
	for (i = 0; i < DIM; i++) {
		if (occup[i] && strcmp(index[i].nom, nom) == 0)
			PrintPers(perso[index[i].adresse]);
	}
}

void Ajouter(PERS perso[DIM], bit occup[DIM],
	INDEX index[DIM], const PERS ajout)
{
	short i;

	for (i = 0; i < DIM && occup[i]; i++); /* Premier libre */

	if (i < DIM) {
		perso[index[i].adresse] = ajout;
		strcpy(index[i].nom, ajout.nom);
		occup[i] = 1;

	        qsort(index, DIM, sizeof(INDEX), IndexComparator);
	} else
		printf("Complet");
}

void Supprimer(PERS perso[DIM], bit occup[DIM],
        INDEX index[DIM], const char nom[NOM_LONG])
{
	short i;

	for (i = 0; i < DIM; i++) {
                if (occup[i] && strcmp(index[i].nom, nom) == 0)
                        occup[i] = 0;
        }
}

void Trace(const PERS perso[DIM], const bit occup[DIM],
	const INDEX index[DIM])
{
	short i;

	printf("Occupation:\n");
	for (i = 0; i < DIM; i++)
		printf("%hd\t", occup[i]);

	printf("Index:\n");
	for (i = 0; i < DIM; i++) {
		printf("%s\t%hd\n",
			index[i].nom, index[i].adresse);
	}

	printf("Personnes:\n");                   
        for (i = 0; i < DIM; i++) {           
                PrintPers(perso[i]);
        }
} 

int main(void) 
{
	bit occup[DIM] = { 1, 0, 1, 1, 0 };
	INDEX index[DIM];
	PERS perso[DIM] = {
		{ 127, "Jean", "Dupont", { 29, 3, 1980 } },
		{ 205, "Jean", "Durand", { 20, 8, 1975 } },
		{ 135, "Marc", "Dupond", { 1, 2, 1978 } },
		{ 128, "Julien", "Pire", { 10, 5, 1979 } },
		{ 112, "Xavier", "Meurice", { 25, 10, 1981 } }
	};
	PERS ajoute = { 134, "Raphael", "Javaux", { 6, 3, 1991 } };

	InitIndex(perso, index);

	Liste(perso, occup, index);

	Recherche(perso, occup, index, "Dupond");

	Ajouter(perso, occup, index, ajoute);

	Liste(perso, occup, index);

	Supprimer(perso, occup, index, "Javaux");
	
	Liste(perso, occup, index);

	Trace(perso, occup, index);

	return 0;
}
