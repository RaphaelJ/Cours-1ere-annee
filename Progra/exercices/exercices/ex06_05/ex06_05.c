#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef unsigned char bool;
#define true 1
#define false 0

bool isInt(char caract)
{
	return caract >= '0' && caract <= '9';
}
bool isLetter(char caract)
{
	return caract >= 'a' && caract <= 'z';
}

char* getEmail(char *chaine)
{ /*		USER@DOMAIN.TLD */
  /* token :   01222344444456789 */
	int token = 0;
	char *pChaine, c;
	int indice;
	bool isValid = true;
	
	fflush(stdin);

	pChaine = chaine;
	for (indice = 0; indice < (MAX_SIZE - 1) && isValid; indice++) {
		c = getchar();
		if ((token == 0 && isLetter(c)) // Première lettre USER
			|| (token == 1 && c == '@') // @
			|| (token == 2 && isLetter(c)) // première lettre DOMAIN
			|| (token == 3 && c == '.') // .
			|| ((token == 4 || token == 5 || token == 6 || token == 7) && isLetter(c))) // lettres TLD
		{
			*pChaine = c;
			*pChaine++;
			token++;
		}
		else if ((token == 1 && isLetter(c)) // Lettres suivantes de USER
			|| (token == 3 && isLetter(c))) // Lettres suivantes de DOMAIN
		{
			*pChaine = c;
			*pChaine++;
		}
		else if (c == '\n')
			break;
		else
		{
			isValid = false;
		}
	}

	if (!isValid || token < 7)
		printf("Chaine invalide");
	
	*pChaine = '\0';
	
	return chaine;
}

int main(void) 
{
	char str[MAX_SIZE];

	printf("Entrez une adresse email: ");
	getEmail(str);

	printf("\nVotre adresse email: %s\n", str);
}
