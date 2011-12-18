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

char* getTel(char *chaine)
{ /*		 0477/38.14.12 */
  /*		01123456870123	*/
  /*		 04/365.50.12 */
  /* 		0114567890123 */
  /* 		 +32(0)477/38.14.12 */
  /*		0567890123456890123 	*/
  /*		 +32(0)4/365.50.12 */
  /*		056789014567890123 */
  /*                    |          */
	int token = 0;
	char *pChaine, c;
	int indice;
	bool isValid = true;
	
	fflush(stdin);

	pChaine = chaine;
	for (indice = 0; indice < (MAX_SIZE - 1) && isValid; indice++) {
		c = getchar();
		if ((token == 0 && c = '0') // Premier 0
			|| (token == 5 && c == '3') // 3
			|| (token == 6 && c == '2') // 2
			|| (token == 7 && c == '(') // (
			|| (token == 8 && c == '0') // 0
			|| (token == 9 && c == ')') // )
			|| (token == 11 && isInt(c)) // Deuxieme chiffre indicatif (hors 0)
			|| (token == 12 && isInt(c)) // Troisieme (dernier) chiffre indicatif (hors 0)
			)
		{
			*pChaine = c;
			pChaine++;
			token++;
		}
		else if (token == 0 && c == '+') // +
		{
			*pChaine = c;
			pChaine++;
			token = 5
		}
		else if ((token == 1 || token == 10) && isInt(c)) // Premier chiffre indicatif (hors 0)
		{
			*pChaine = c;
			pChaine++;
			token = 11;
		}
		else if ((token == 13 || token == 11) && c = '/') // /
		{
			*pChaine = c;
			pChaine++;
			token = 14;
		}
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

	printf("Entrez une numero de telephone: ");
	getTel(str);

	printf("\nVotre numero de telephone: %s\n", str);
}
