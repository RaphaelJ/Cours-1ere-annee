#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 50

typedef unsigned char bool;
#define true 1
#define false 0

bool isInt(char caract)
{
	return caract >= '0' && caract <= '9';
}

short charToInt(char* str, short len)
{
	short val = 0;
	for (; len > 0; str++, len--)
		val += (*str - '0') * (short) pow(10, len - 1);
	return val;
}

bool validDate(char *str)
{
	short jour, mois, annee;

	jour = charToInt(str, 2);
	mois = charToInt(str + 3, 2);
	annee = charToInt(str + 6, 4);

	return jour > 0 && mois > 0 &&
		 (mois == 2 && (((annee % 4 == 0 && annee % 100) || annee % 400 == 1) && jour <= 29) || jour < 28)
		  || (mois % 2 == 1 && mois <= 7 && jour < 31)
		  || (mois % 2 == 0 && mois <= 7 && jour < 30) // TODO: Combiner ces conditions
		  || (mois % 2 == 1 && mois > 7 && jour < 30)
		  || (mois % 2 == 0 && mois > 7 && jour < 31);
}

char* getDate(char *chaine)
{ /*			JJ/MM/AAAA */
  /* token :   01234567890 */
	int token = 0;
	char *pChaine, c;
	int indice;
	bool isValid = true;
	
	fflush(stdin);

	pChaine = chaine;
	for (indice = 0; indice < (MAX_SIZE - 1) && isValid; indice++) {
		c = getchar();
		if (((token == 0 // Premier J
				|| token == 1 // Deuxieme J
				|| token == 3 // Premier M
				|| token == 4 // Deuxième M
				|| token == 6 // Premier A
				|| token == 7 // Deuxième M
				|| token == 8 // Troisième M
				|| token == 9) // Quatrième M
				&& isInt(c))
			|| ((token == 2
				|| token == 5)
				&& c == '/')
			)
		{
			*pChaine = c;
			*pChaine++;
			token++;
		}
		else if (c == '\n')
			break;
		else
		{
			isValid = false;
		}
	}

	if (!isValid || token < 10 || !validDate(chaine))
		printf("Chaine invalide");
	
	*pChaine = '\0';
	
	return chaine;
}

int main(void) 
{
	char str[MAX_SIZE];

	printf("Entrez une date: ");
	getDate(str);

	printf("\nDate: %s\n", str);
}