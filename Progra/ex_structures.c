#include <stdio.h>
#include <stdlib.h>

#define MAXCLIENTS 20
#define NOM_LEN 25
#define PRENOM_LEN 20
#define RUE_LEN 50
#define VILLE_LEN 15
#define EMAIL_LEN 30

typedef char byte;
typedef unsigned int uint;
typedef char bool;
#define true 1
#define false 0

typedef struct _Allocator {
	uint availaible : MAXCLIENTS;
} Allocator;

typedef struct _Lieu {
	char rue[RUE_LEN];
	char ville[VILLE_LEN];
} Lieu;

typedef struct _Date {
	byte jour;
	byte mois;
	short annee;
} Date;

typedef struct _Fiche {
	int id;
	char nom[NOM_LEN];
	char prenom[PRENOM_LEN];
	Date naissance;
	Lieu adresse;
	char email[EMAIL_LEN];
} Fiche;

void allocSet(Allocator *alloc, int indice, bool val);
int allocGetFree(Allocator *alloc);

int main()
{
	Allocator alloc;
	Fiche fiches[MAXCLIENTS];

	alloc.availaible = 0; /* Tout libre */
	
	allocSet(&alloc, 0, 1);
	printf("%d", allocGetFree(&alloc));
}

void allocSet(Allocator *alloc, int indice, bool val)
{
	if (val == 0) {
		if ((alloc->availaible >> indice) % 2 == 1)
			alloc->availaible = ;
	} else
		alloc->availaible |= (int) val << indice;
}

int allocGetFree(Allocator *alloc)
{
	int indice;
	for (indice = 0; indice < MAXCLIENTS && (alloc->availaible >> indice) % 2; indice++);
	
	if (indice == MAX_CLIENT)
		return -1;
	else
		return indice;
}
