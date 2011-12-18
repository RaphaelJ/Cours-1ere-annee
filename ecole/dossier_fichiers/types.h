#ifndef _TYPES_H
#define _TYPES_H 1

#include <time.h>

typedef char bool;
enum { false, true };

typedef unsigned char byte;

typedef int rowid;

typedef struct _DATE {
	byte jour;
	byte mois;
	short annee;
} DATE;

typedef struct _HEURE {
	byte heures;
	byte minutes;
} HEURE;

typedef struct _PAYS {
	char* nom;
	char* regex_tel;
	char* regex_cp;
} PAYS;

/* Liste des pays avec regex des téléphones et codes postaux */
#define NB_PAYS 8
static PAYS pays[] = {
	/* http://fr.wikipedia.org/wiki/Numéro_de_téléphone
	 * http://fr.wikipedia.org/wiki/Code_Postal */
	{ "Belgique",
	  "0[1-9][0-9]?[/ ]?[0-9]{2,3}[. ]?[0-9]{2,2}[. ]?[0-9]{2,2}",
	  "[0-9]{4,4}" },
	{ "Espagne",
	  "[0-9]{3,3}.?[0-9]{2,2}.?[0-9]{2,2}.?[0-9]{2,2}",
	  "[0-9]{5,5}" },
	{ "France",
	  "0 ?[0-9] ?[0,9]{2,2} ?[0,9]{2,2} ?[0,9]{2,2} [0,9]{2,2}",
	  "[0-9]{5,5}" },
	{ "Luxembourg",
	  "4 ?[0-9]{3,3} ?[0-9]{2,2}",
	  "[0-9]{4,4}" },
	{ "Pays-Bas",
	  "0[0-9]{2,3}-?[0-9]{6,7}",
	  "[0-9]{4,4} ?[A-Z]{2,2}" },
	{ "Suisse",
	  "0[0-9]{2,2} ?[0-9]{3,3} ?[0-9]{2,2} ?[0-9]{2,2}",
	  "[0-9]{4,4}" },
	{ "UK",
	  "01[A-Z]{3,3} ?[A-Z]{5,6}",
	  "[A-Z0-9]{2,4} ?[0-9][A-Z]{2,2}" },
	{ "USA",
	  "[0-9]{3,3} ?[0-9]{3,3}-?[0-9]{4,4}",
	  "[0-9]{5,5}" }
	/* ... */
};

#endif
