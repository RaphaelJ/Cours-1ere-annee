#ifndef _DB_H
#define _DB_H 1

#define LIBRE -1
#define FIN -1

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

#define TAILLE_NOM_FICHIER 75

#define FICHIER_JEUX "jeux"
#define FICHIER_JOUEURS "joueurs"
#define FICHIER_PARTIES "parties"

#define sort(A,B,C,D) qsort(A,B,C,D)
/* #define sort(A,B,C,D) heapsort(A,B,C,D) */

/* Séparateur de répertoire */
#ifdef WIN32
	#define SEPARATEUR "\\"
#else
	#define SEPARATEUR "/"
#endif

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
	rowid ligne;

	int idJeu;
	char nom[TAILLE_NOM_JEU];
} JEU_INDEX;

typedef struct _JEUX {
	int nbJeux;
	JEU_INDEX index[NB_JEUX];

	char fichier[TAILLE_NOM_FICHIER];
} JEUX;

typedef struct _JOUEUR {
	rowid suivant;

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

typedef struct _POINTEURS {
	rowid libre;
	rowid occupe;
} POINTEURS;
typedef struct _JOUEURS {
	POINTEURS pointeurs;
	
	char fichier[TAILLE_NOM_FICHIER];
} JOUEURS;

typedef struct _PARTIE {
	rowid idJoueur;
	rowid idJeu;
	DATE date;
	HEURE heure;
	byte points;
} PARTIE;

typedef struct _PARTIES {
	char fichier[TAILLE_NOM_FICHIER];
} PARTIES;

typedef struct _DB {
	JEUX jeux;
	JOUEURS joueurs;
	PARTIES parties;
} DB;

void ouvrirBd(DB* bd, const char* repertoire);

int jeuIndexCmp(const void* p1, const void* p2);
void ouvrirJeux(JEUX* jeux, const char* repertoire);
rowid idJeuExiste(DB* bd, const int idJeu);
JEU_INDEX* nouveauJeu(DB* bd);
JEU_INDEX* chercherJeu(DB* bd, char* nom);
JEU donneesJeu(DB* bd, const JEU_INDEX index);
void changerJeu(DB* bd, const JEU_INDEX index, const JEU jeu);
void retirerJeu(DB* bd, JEU_INDEX* index);
void listerJeux(DB* bd);
 
void ouvrirJoueurs(JOUEURS* joueurs, const char* repertoire);
rowid idJoueurExiste(DB* bd, const int idJoueur);
int joueurCmp(const void* p1, const void* p2);
void nouveauJoueur(DB* bd, JOUEUR joueur);
void listageJoueurs(DB* bd, bool majeurs);

void ouvrirParties(PARTIES* parties, const char* repertoire);
void nouvellePartie(DB* bd, PARTIE partie);
void listerParties(DB* bd);
void supprimerParties(DB* bd, rowid jeuRowId);

#endif
