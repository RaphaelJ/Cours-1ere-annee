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
 *
 * Rmk: La fonction est longue et pourrait être repartie
 * sur plusieurs fonctions, mais il serait nécéssaire
 * d'utiliser des doubles indirections sur l'expression
 * régulière, ce qui ne rend le fonctionnement plus
 * complexe. */
REGEX tokenize(const char* s_regex)
{
	REGEX regex;
	
	TOKEN* currToken;
	MODIFIER* currModifier;

	regex.nTokens = 0;
	
	while (*s_regex != '\0' && regex.nTokens < MAX_TOKENS) {
		currToken = &regex.tokens[regex.nTokens];
		
		if (*s_regex == '[') { /* Crochets */
			T_BRACKETS* brackets = &currToken->token.brackets;

			currToken->check = checkBrackets;

			brackets->nRanges = 0;
			brackets->nConstants = 0;

			s_regex++; /* Passe le [ */
			do {
				/* Gamme de caractères */
				if (*(s_regex + 1) == '-'
				    && *(s_regex + 2) != ']') {
					T_RANGE* range
					    = &brackets->ranges[brackets->nRanges];					
					byte a, b;
					
					a = *s_regex;
					s_regex += 2; /* Passe le - */
					b = *s_regex;

					if (a < b) { /* Démarre au minimum */
						range->start = a;
						range->stop = b;
					} else {
						range->start = b;
						range->stop = a;
					}
	
					brackets->nRanges++;
				} else { /* Constante */
					brackets->constants[brackets->nConstants] =
					    (T_CONSTANT) *s_regex;
	
					brackets->nConstants++;
				}

				s_regex++;
			} while (*s_regex != ']'
			    && brackets->nRanges < MAX_BRACKETS_TOKENS
			    && brackets->nConstants < MAX_BRACKETS_TOKENS);
		} else { /* Constante */
			currToken->check = checkConstant;
			currToken->token.constant = (T_CONSTANT) *s_regex;
		}
	
		/* Analyse le modificateur de répétitions */
		currModifier = &(currToken->modifier);
		currModifier->current = 0;
	
		s_regex++;
		switch (*s_regex) {
	        case '?': /* 0 ou une fois */
	                currModifier->min = 0;
	                currModifier->max = 1;
	                currToken->filled = true;
	                s_regex++;
	                break;
        	case '*': /* 0 fois ou plus */
	                currModifier->min = 0;
	                currModifier->max = REPEAT_NO_LIMIT;
	                currToken->filled = true;
	                s_regex++;
	                break;
        	case '+': /* Une fois ou plus */
	                currModifier->min = 1;
	                currModifier->max = REPEAT_NO_LIMIT;
	                currToken->filled = false;
	                s_regex++;
        	        break;
	        case '{': /* Personnalisé */
	                /* FIXME: Uniquement des nombres de 0 à 9 */
		        currModifier->min = *(++s_regex) - '0';
	                s_regex++; /* Passe le , */
	                currModifier->max = *(++s_regex) - '0';
	                s_regex += 2; /* Passe le } */
        	        currToken->filled = (currModifier->min == 0);
	                break;
        	default: /* Pas de modificateur: une seule fois */
	                currModifier->min = 1;
	                currModifier->max = 1;
        	        currToken->filled = false;
	        }
		
		regex.nTokens++;
	}

	return regex;
}

/* Vérifie si un caractère respecte les conditions
 * d'une expression placée entre crochets.
 * Voir TOKEN.check() */
bool checkBrackets(const TOKEN_TYPE token, const char charac)
{
	const T_BRACKETS brackets = token.brackets;
	byte i;
	
	/* Vérifie si le caractere est dans les gammes de caractères */
	for (i = 0; i < brackets.nRanges; i++) {
		if (charac >= brackets.ranges[i].start
		    && charac <= brackets.ranges[i].stop)
			return true;
	}

	/* Vérifie si le caractère fait partie des constantes */
	for (i = 0; i < brackets.nConstants; i++) {
		if (charac == (char) brackets.constants[i])
			return true;
	}

	return false;
}

/* Vérifie si un caractère est identique à un TOKEN de type
 * constante.
 * Voir TOKEN.check() */
bool checkConstant(const TOKEN_TYPE token, const char charac)
{
	return token.constant == charac;
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

				if (maxRepeats(*token))
					iToken++;
				else if (token->check(token->token, c)) {
					MODIFIER* modifier = &(token->modifier);
					modifier->current++;
					token->filled
					    = (modifier->current >= modifier->min);
					break; /* Caractère suivant */
				} else if (!token->filled)
					valid = false;
				else
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

/* Renvoie true si le TOKEN a atteint son nombre maximal
 * de répétitions.
 *
 * @token: TOKEN à vérifier.
 *
 * Sortie: true si le nombre maximal est atteint. */
bool maxRepeats(const TOKEN token)
{
	return token.modifier.max != REPEAT_NO_LIMIT
	    && token.modifier.current >= token.modifier.max;
}
