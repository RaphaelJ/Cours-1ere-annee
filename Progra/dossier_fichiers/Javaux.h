#ifndef _JAVAUX_H
#define _JAVAUX_H 1

#include "types.h"

typedef struct _MENU_OPTION {
	char* libelle;
	
	void (*action)(DB*);
} MENU_OPTION;


void menu(DB* bd, MENU_OPTION* options, short nbOptions);

void menuPrincipal(DB* bd);

void menuJeux(DB* bd);
void menuJoueurs(DB* bd);
void menuParties(DB* bd);

void editerFicheJeu(DB* bd, JEU_INDEX* index, bool nouveau);
void ajouterJeu(DB* bd);
JEU_INDEX* trouverJeu(DB* bd);
void modifierJeu(DB* bd);
void supprimerJeu(DB* bd);

void ajouterJoueur(DB* bd);
void listerJoueurs(DB* bd);
void listerJoueursMajeurs(DB* bd);

void gererPartie(DB* bd);

void editerIdentifiant(DB* bd, char* libelle, int* valeur,
	rowid (*verifExiste)(DB* bd, const int id), bool nouveau);
void editerNom(char* libelle, char* valeur, bool nouveau);
void editerBooleen(char* libelle, bool* valeur, bool nouveau);
void editerNombre(char* libelle, short* valeur, short min, bool nouveau);
void editerDate(char* libelle, DATE* valeur, bool nouveau, bool passe);
void entrerPays(byte* idPays);
void entrerRegex(char* libelle, char* regex,
	char* resultat, bool obligatoire);

#endif
