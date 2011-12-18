#ifndef _JAVAUX_H
#define _JAVAUX_H 1

#include "types.h"

#define LIBRE -1

#define NB_JEUX 15
#define NB_JOUEURS 15
#define NB_PARTIES 15

#define TAILLE_NOM_JEU 15

#define TAILLE_NOM 25
#define TAILLE_PRENOM TAILLE_NOM
#define TAILLE_ADRESSE 30
#define TAILLE_VILLE 25
#define TAILLE_CP 10
#define TAILLE_TEL 20
#define TAILLE_EMAIL 65

/*#define TAILLE_PAYS 25
#define TAILLE_REGEX_TEL 75
#define TAILLE_REGEX_CP 40*/

#define sort(A,B,C,D) qsort(A,B,C,D)
/*#define sort(A,B,C,D) heapsort(A,B,C,D)*/

typedef struct _DATE {
	byte jour;
	byte mois;
	short annee;
} DATE;

typedef struct _HEURE {
	byte heures;
	byte minutes;
} HEURE;

typedef struct _JEU {
	int idJeu;
	char nom[TAILLE_NOM_JEU];
	bool interieur;
	bool exterieur;
	short ageMin;
	short ageMax;
	short nbJoueursMin;
	short nbJoueursMax;
	DATE dateAchat;
	short garantie;
} JEU;

typedef struct _JEU_INDEX {
	JEU* donnees;

	int idJeu;
	char* nom;
} JEU_INDEX;

typedef struct _JEUX {
	short nb;

	JEU_INDEX index[NB_JEUX];

	JEU vect[NB_JEUX];
} JEUX;

typedef struct _JOUEUR {
	struct _JOUEUR* suivant;

	int idJoueur;
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
	DATE dateNaissance;
	byte pays;
	short numero;
	char adresse[TAILLE_ADRESSE];
	char codePostal[TAILLE_CP];
	char ville[TAILLE_VILLE];
	char telephone[TAILLE_TEL];
	char email[TAILLE_EMAIL];
} JOUEUR;

typedef struct _JOUEURS {
	JOUEUR* libre;
	JOUEUR* occupe;
	
	JOUEUR vect[NB_JOUEURS];
} JOUEURS;

typedef struct _PARTIE {
	bool libre;	

	int idJoueur;
	int idJeu;
	DATE date;
	HEURE heure;
	short points;
} PARTIE;

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
	  "0[1-9][0-9]?/? ?[0-9]{2,3}.? ?[0-9]{2,2}.? ?[0-9]{2,2}",
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

typedef struct _MENU_OPTION {
	char* libelle;
	
	void (*action)(void);
} MENU_OPTION;

void initTabs(void);

void menu(MENU_OPTION* options, short nbOptions);
void menuPrincipal(void);

void menuJeux(void);
void menuJoueurs(void);
void menuParties(void);

bool idJeuExiste(int idJeu);
bool idJoueurExiste(int idJoueur);

void editerFicheJeu(JEU_INDEX* index, bool nouveau);
int indexcmp(const void* i1, const void* i2);
void ajouterJeu(void);
short trouverJeu(void);
void modifierJeu(void);
void supprimerJeu(void);
void listerJeux(void);

void ajouterJoueur();
void listageJoueurs(bool majeurs);
void listerJoueurs();
void listerJoueursMajeurs();

void gererPartie(void);
void listerParties(void);

bool anneeBissextile(const DATE date);
short joursMois(const DATE date);
bool datePassee(const DATE date);
bool dateValide(const DATE date);
short age(const DATE date);

void editerIdentifiant(char* libelle, int* valeur,
	bool (*verifExiste)(int id), bool nouveau);
void editerNom(char* libelle, char* valeur, bool nouveau);
void editerBooleen(char* libelle, bool* valeur, bool nouveau);
void editerNombre(char* libelle, short* valeur, short min, bool nouveau);
void editerDate(char* libelle, DATE* valeur, bool nouveau, bool passe);
void entrerPays(byte* idPays);
void entrerRegex(char* libelle, char* regex,
	char* resultat, bool obligatoire);

#endif