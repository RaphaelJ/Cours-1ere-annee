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

char* getString(char *chaine)
{
	char *pChaine, c;
	int indice;
	
	fflush(stdin);

	pChaine = chaine;
	for (indice = 0; indice < (MAX_SIZE - 1); indice++) {
		c = getchar();
		if (c != '\n' && isInt(c)) {
			*pChaine = c;
			pChaine++;
		} else 
			break;
	}

	*pChaine = '\0';
	return chaine;
}

int main(void) 
{
	char str[MAX_SIZE];

	printf("Entrez une chaine: ");
	getString(str);

	printf("\nVotre chaine: %s\n", str);
}