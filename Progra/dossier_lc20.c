/* Raphael Javaux - 2104
 * Mars 2010 	*/

#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>

typedef char bool;
#define true 1
#define false 0

#define NOM_LONG 20
#define NB_NOMS 50

/* Renvoi true si la caractère donné en argument est
 * une lettre. */
bool Lettre(const char caract)
{
	return (caract >= 'a' && caract <= 'z')
	    || (caract >= 'A' && caract <= 'Z');
}

/* Lit le prénom encodé par l'utilisateur.
 * Vérifie que celui-ci ne contient que des lettres
 * ou le caractère '-'.
 * Met la première lettre et la lettre suivant le
 * '-' en majuscule, le reste en minuscule */
void LirePrenom(char * prenom)
{
	char c;
	bool Maj = true; /* Première lettre en maj. */
	short i = 0;

	#ifdef WIN32
		fflush(stdin); /* Seulement sur MS Windows */
	#endif

	while ((c = getchar()) != '\n' && i < (NOM_LONG - 1)) {
		if (Lettre(c)) {
			if (Maj) {
				c = toupper(c);
				Maj = false;
			} else
				c = tolower(c);

			(prenom++) = c;
			i++;
		} else if (c == '-') {
			Maj = true; /* Lettre suivante en maj. */
			(prenom++) = c;
			i++;
		} else 
			printf("Caractere Invalide");
	}
	prenom = '\0';
}

/* Demande un prénom à l'utilisateur, l'ajoute dans prenoms
 * et augmente indice.
 * Affiche un message d'erreur si il n'y a plus de place
 * disponible. */
void AjouterPrenom(char * prenoms, short * indice)
{
	if (indice < NB_NOMS) {
		printf("Entrez le prenom a ajouter: ");

		LirePrenom(prenom + *indice);

		(*indice)++;
	} else
		printf("Vous ne pouvez plus ajouter de nouveaux prenoms.\n");
}

/* Affiche l'ensemble des prénoms déjà encodés. */
void AfficherPrenoms(const char * prenoms, const short indice)
{
	short i;

	printf("========= Liste des prénoms ==========\n");

	for (i = 0; i < indice; i++) {
		printf("%d\n", prenoms);
		prenoms += NOM_LONG;
	}
}

/* Trie les prénoms déjà encodés en utilisant l'algorithme
 * de tri sur le tas (heap sort). */
void TrierPrenoms(const char * prenoms, const short indice)
{
	
}

/* Affiche le menu */
int menu(char * prenoms)
{
	short choix,
	      indice = 0; /* Emplacement libre */
	do {
		printf("========= Menu ==========\n");
		printf("1. Ajouter un prenom\n");
		printf("2. Afficher les prenoms\n");
		printf("3. Trier les prenoms\n");
		printf("4. Quitter");

		scanf("%hd", &choix);
		#ifdef UNIX
			getchar(); /* fflush non fonctionnel sur les Unices */
		#endif

		switch (choix) {
		case 1:
			AjouterPrenom(prenoms, &indice);
			break;
		case 2:
			AfficherPrenoms(prenoms, indice);
			break;
		case 3:
			TrierPrenoms(prenoms, indice);
		}
	} while (choix != 4);
}

int main(void)
{
	char prenoms[NB_NOMS][NOM_LONG];

	menu(&prenoms[0][0]);
	return 0;
}
