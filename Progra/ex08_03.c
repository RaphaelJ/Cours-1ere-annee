#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define FICHIER "fichier"

#define TAILLE 15

#define TAILLE_NOM 15
#define TAILLE_PRENOM TAILLE_NOM

#define TAILLE_RUE 40
#define TAILLE_LOCALITE 15

#define LIBRE -1 /* ID Libre */

typedef char byte;
typedef char bool;
enum { false, true };

typedef struct _ADRESSE {
	char rue[TAILLE_RUE];
	short codePostal;
	char localite[TAILLE_LOCALITE];
} ADRESSE;

typedef struct _DATE {
	byte jour;
	byte mois;
	short annee;
} DATE;

typedef struct _DATA {
	short id;
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
} DATA;

typedef struct _DATA_INDEX {
	short position;
	
	short id;
	char nom[TAILLE_NOM];
} DATA_INDEX;

static DATA_INDEX index[TAILLE];

/* Compare deux éléments de l'index. */
int indexCmp(const DATA_INDEX* i1, const DATA_INDEX* i2)
{
	if (i1->id != LIBRE) {
		if (i2->id == LIBRE) /* Libres en derniers */
			return -1;
		else /* Libres identiques */
			return 0;
	} else if (!i2->id != LIBRE) /* i1 libre, i2 OQP. i2 premier */
		return 1;
	else /* i1 et i2 OQP, comparaison du nom */
		return strcmp(i1->nom, i2->nom);
}

/* Créer un fichier et un index vide. */
void bidonnerFichier()
{
	FILE* fp = fopen(FICHIER, "wb");
	DATA vide = { LIBRE };
	short i;
	
	for (i = 0; i < TAILLE; i++) {
		fwrite(&vide, sizeof vide, 1, fp);
		
		index[i].id = LIBRE;
		index[i].position = i;
	}

	fclose(fp);
}

/* Génère l'index à partir du fichier */
void genererIndex()
{
	FILE* fp = fopen(FICHIER, "rb");
	DATA data;
	short i;
	
	for (i = 0; i < TAILLE; i++) {
		fread(&data, sizeof data, 1, fp);

		index[i].position = i;
		index[i].id = data.id;

		if (data.id != LIBRE)
			index[i].nom = data.nom;
	}
	
	fclose(fp);
}

/* Vérifie si le fichier existe.
 * Le crée et le bidonne le cas échéant. */
void verifierFichier()
{
	FILE* fp = fopen(FICHIER, "rb");
	bool exists = (fp != NULL);
	fclose(fp);

	if (!exists) /* Nouveau fichier */
		bidonnerFichier();
	 else
		genererIndex();
}

int main(void)
{
	DATA_INDEX index[TAILLE];

	verifierFichier();
}
