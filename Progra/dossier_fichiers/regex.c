#include <stdio.h>
#include <stdlib.h>

#include "regex.h"

/* « Complie » une expression régulière en un vecteur
 * de tokens.
 * 
 * @s_regex: chaine représentant l'expression régulière
 *	à compiler.
 *
 * Sortie: structure REGEX contenant le vecteur de tokens.
 */
REGEX tokenize(const char* s_regex)
{
	REGEX regex;
	TOKEN* currToken;

	regex.nTokens = 0;
	
	currToken = &regex.tokens[regex.nTokens];
	while (*s_regex != '\0' && *s_regex != ')'
	    && regex.nTokens < MAX_TOKENS) {
		if (*s_regex == '[') /* Crochets */
			tokenizeBrackets(currToken, &s_regex);
		else { /* Constante */
			currToken->check = checkConstant;
			currToken->token.constant = (T_CONSTANT) *s_regex;
			*s_regex++;
		}

		tokenizeModifier(currToken, &s_regex);

		/* Passe au token suivant */
		regex.nTokens++;
		currToken = &regex.tokens[regex.nTokens];
	}
	return regex;
}

/* Interprete une expression entre crochets.
 *
 * @currToken: pointeur vers le token qui contiendra l'expression
 *	entre crochets ;
 * @s_regex: pointeur vers chaine contenant l'expression
 *	entre crochets à interpretter.
 * */
void tokenizeBrackets(TOKEN* currToken, const char** s_regex)
{
	T_BRACKETS* brackets = &currToken->token.brackets;
	
	currToken->check = checkBrackets;

	brackets->nRanges = 0;
	brackets->nConstants = 0;

	(*s_regex)++; /* Passe le [ */
	do {
		/* Gamme de caractères */
		if (*(*s_regex + 1) == '-'
		    && *(*s_regex + 2) != ']') {
			T_RANGE* range
			    = &brackets->ranges[brackets->nRanges];					
			byte a, b;
					
			a = **s_regex;
			(*s_regex) += 2; /* Passe le - */
			b = **s_regex;

			if (a < b) { /* Démarre au minimum */
				range->start = a;
				range->stop = b;
			} else {
				range->start = b;
				range->stop = a;
			}
	
			brackets->nRanges++;
		} else { /* Constante */
			brackets->constants[brackets->nConstants]
			    = (T_CONSTANT) **s_regex;
	
			brackets->nConstants++;
		}

		(*s_regex)++;
	} while (**s_regex != ']'
		&& brackets->nRanges < MAX_BRACKETS_TOKENS
		&& brackets->nConstants < MAX_BRACKETS_TOKENS);

	(*s_regex)++; /* Passe le ] */
}

/* Interprete un modifieur de répetition.
 *
 * @currToken: pointeur vers le token (pour initialiser le filled
 *	et le maxRepeats) ;
 * @s_regex: pointeur vers chaine contenant le modificateur
 *	à interpretter.
 * */
void tokenizeModifier(TOKEN* currToken, const char** s_regex)
{
	MODIFIER* currModifier = &currToken->modifier;

	/* Analyse le modificateur de répétitions */
	currModifier->current = 0;
	
	switch (**s_regex) {
        case '?': /* 0 ou une fois */
                currModifier->min = 0;
                currModifier->max = 1;
                currToken->filled = true;
                (*s_regex)++;
                break;
       	case '*': /* 0 fois ou plus */
                currModifier->min = 0;
                currModifier->max = REPEAT_NO_LIMIT;
                currToken->filled = true;
                (*s_regex)++;
                break;
       	case '+': /* Une fois ou plus */
                currModifier->min = 1;
                currModifier->max = REPEAT_NO_LIMIT;
                currToken->filled = false;
                (*s_regex)++;
       	        break;
        case '{': /* Personnalisé */
                /* FIXME: Uniquement des nombres de 0 à 9 */
	        currModifier->min = *(++(*s_regex)) - '0';
                (*s_regex)++; /* Passe le , */
                currModifier->max = *(++(*s_regex)) - '0';
                *s_regex += 2; /* Passe le } */
       	        currToken->filled = (currModifier->min == 0);
                break;
       	default: /* Pas de modificateur: une seule fois */
                currModifier->min = 1;
                currModifier->max = 1;
       	        currToken->filled = false;
        }

	/* On pourrait mettre le minimum à 0 ... */
	currToken->maxRepeats = (currModifier->min <= 0);
}

/* Met à jour les valeurs de filled et de maxRepeats
 * par rapport au modificateur de répétition.
 *
 * @token: pointeur vers le token a mettre à jour ;
 * @modifier: modificateur à analyser. */
void updateModifier(TOKEN* token, const MODIFIER modifier)
{
	token->filled
	    = (modifier.current >= modifier.min);

	token->maxRepeats
	    = (modifier.max != REPEAT_NO_LIMIT
	       && modifier.current >= modifier.max);
}

/* Renvoi true si le caractère respecte une des conditions
 * énoncées dans une expression entre crochets.
 *
 * @brackets: expression entre crochets ;
 * @charac: caractère a vérifier.
 *
 * Sortie: true si charac respecte l'une des conditions du
 * 	brackets. */
bool _checkBrackets(const T_BRACKETS brackets, const char charac)
{
	byte i;
	
	/* Vérifie si le caractere est dans les gammes de caractères */
	for (i = 0; i < brackets.nRanges; i++) {
		if (charac >= brackets.ranges[i].start
		    && charac <= brackets.ranges[i].stop)
			return true;
	}

	/* Vérifie si le caractère fait partie des constantes */
	for (i = 0; i < brackets.nConstants; i++) {
		if (charac == brackets.constants[i])
			return true;
	}

	return false;
}

/* Vérifie si un caractère respecte les conditions
 * d'une expression placée entre crochets.
 * Voir TOKEN.check() */
bool checkBrackets(TOKEN* token, const char charac)
{
	const T_BRACKETS brackets = token->token.brackets;
	
	if (!_checkBrackets(brackets, charac))
		return false;
	else {
		MODIFIER* modifier = &(token->modifier);
		
		modifier->current++;
		updateModifier(token, *modifier);

		return true;
	}
}

/* Vérifie si un caractère est identique à un TOKEN de type
 * constante.
 * Voir TOKEN.check() */
bool checkConstant(TOKEN* token, const char charac)
{
	if (token->token.constant != charac)
		return false;
	else { 
		MODIFIER* modifier = &(token->modifier);

		modifier->current++;
		updateModifier(token, *modifier);
	
		return true;
	}
}

/* Récupère une chaine de caractères de l'entrée standard en
 * vérifiant si elle respecte les conditions imposées par
 * l'expression régulière.
 *
 * @regex: Expression régulière à vérifier ;
 * @out: Chaine entrée sur l'entrée standard.
 * 
 * Sortie: Booléan retournant true si l'entrée respecte
 * 	l'expression régulière.
 */
bool regex_scanf(const char* s_regex, char* out)
{
	REGEX regex = tokenize(s_regex);
	bool valid = true;
	byte iToken = 0;
	char c;

	#ifdef WIN32
        fflush(stdin);
	#endif
	
	while ((c = getchar()) != '\n') {
		while (valid) {
			if (iToken >= regex.nTokens)
				valid = false;
			else {
				TOKEN* token = &regex.tokens[iToken];

				if (token->maxRepeats) 
					iToken++; /* Passe au token suivant */
				else if (token->check(token, c))
					break; /* Caractère suivant */
				else if (!token->filled) /* Invalide */
					valid = false;
				else /* Passe au token suivant */
					iToken++;
			}
		}
		
		*(out++) = c;
	}
	*out = '\0';

	if (!valid)
		return false;
	else {
		while (iToken < (regex.nTokens - 1) && regex.tokens[iToken].filled)
			iToken++; /* Passe les éventuels tokens facultatifs */

		return iToken == (regex.nTokens - 1) /* Si le dernier token est */
		    && regex.tokens[iToken].filled; /* satisfait. */
	}
}
