#ifndef _REGEX_H
#define _REGEX_H 1

#include "types.h"

/* Nombre maximal de tokens dans une même
 * expression régulière. */
#define MAX_TOKENS 15
#define MAX_BRACKETS_TOKENS 5

#define REPEAT_NO_LIMIT 0

/* Expression régulières
 * Permet d'utiliser des expressions régulières simplifiées
 * de type POSIX pour obtenir et vérifier des données
 * entrées par l'utilisateur.
 *
 * Accepte les expressions suivantes:
 *	constante: vérifie si une constante est donnée dans
 *		l'expression ;
 *	crochets: vérifie si un caractère est compris dans
 *		un ensemble (une gamme) de caractères ou/et
 *		dans une liste de constantes.
 *
 * Les expressions et les sous-expression acceptent des
 * modificateurs de répétition qui se placent directement après 
 * celles-ci :
 *	?: 0 ou une fois ;
 *	*: 0 fois ou plus ;
 *	+: une fois ou plus ;
 *	{x,y}: entre x et y fois (si y vaut 0, pas de
 *		limite maximum).
 *
 * Exemples:
 *	[A-Za-z0-9]{0,6}: chaine alpha numérique de 0 à 6
 *		caractères ;
 *	[A-Z][A-Za-z- ]+: chaine commencant par une
 *		majuscule et dont le reste est composé de
 *		lettres, d'espaces ou du caractère « - » ;
 *	Coca[- ][Cc]ola: accepte Coca-Cola, Coca-cola,
 *		Coca Cola et Coca cola.
 */

/* Donne des informations de répétition d'un
 * TOKEN. */
typedef struct _MODIFIER {
        byte min;
        byte max;

        /* Nombre de répétitions en cours
         * lors de l'analyse */
        byte current;
} MODIFIER;

/* Token de type constante (caractère, nombre, ...) */
typedef char T_CONSTANT;

/* Token de type « gamme » (de A à Z, de 1 à 5, ...).
 * Utilisable uniquement entre crochets. */
typedef struct _T_RANGE {
        char start;
        char stop;
} T_RANGE;

/* Token de type « crochets », qui peut contenir un 
 * ensemble de constantes ou/et des gammes de caractères.
 * Exemples: 
 *	[A-Z] : lettres majuscules ;
 *	[01] : 0 ou 1 ;
 *	[A-Za-z0-9_] : caractères alpha numeriques ou
 *		caractère « _ ». */
typedef struct _T_BRACKETS {
	byte nConstants;
	T_CONSTANT constants[MAX_BRACKETS_TOKENS];

	byte nRanges;
	T_RANGE ranges[MAX_BRACKETS_TOKENS];
} T_BRACKETS;

/* Type générique apte à contenir les différents types
 * de TOKENs de l'expression régulière. */
typedef union _TOKEN_TYPE {
	T_CONSTANT constant;
	T_BRACKETS brackets;
} TOKEN_TYPE;


/* Stocke un TOKEN, la fonction pour le vérifier,
 * la façon doit il doit se répeter et si ses conditions
 * sont remplies lors de l'analyse. */
typedef struct _TOKEN TOKEN;
struct _TOKEN {
        /* Fonction qui va être appelée pour vérifier
         * si un caractère remplit les conditions du
         * TOKEN. Les champs filled et maxRepeats seront
	 * également modifiés par cette fonction.
	 *
	 * @TOKEN: pointeur vers le token à vérifier ;
	 * @char: caractère à vérifier avec le token.
	 *
	 * Sortie: true si dans le caractère respecte
	 * 	les conditions du token. */
        bool (*check)(TOKEN*, const char);

	/* Informations propres au type du token */
       	TOKEN_TYPE token;

	/* Modificateur de répétition */
	MODIFIER modifier;

        /* Défini si la condition d'existance du
         * token est bien remplie lors de l'analyse
         * de la chaine. */
        bool filled;

	/* Défini si le nombre maximal de répétitions
	 * du token est atteint */
	bool maxRepeats;
};

/* Contient une expression régulière « compilée »
 * par le tokenizer. */
typedef struct _REGEX {
        byte nTokens;
        TOKEN tokens[MAX_TOKENS];
} REGEX;

REGEX tokenize(const char* s_regex);
void tokenizeBrackets(TOKEN* currToken, const char **s_regex);
void tokenizeModifier(TOKEN* currToken, const char** s_regex);

bool _checkBrackets(const T_BRACKETS brackets, const char charac);
bool checkBrackets(TOKEN* token, const char charac);
bool checkConstant(TOKEN* token, const char charac);

bool regex_scanf(const char* s_regex, char* out);

#endif
