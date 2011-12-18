#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include <limits.h> /* Non-Ansi, C99 */

typedef char byte;

typedef byte bool;
#define true 1
#define false 0
/* Rmks:
 * true et false ont une valeur entière et ne sont pas
 * des caractères car cela pourrait causer quelques
 * problèmes avec les conditions implicites :
 * if (boolean) sera toujours évalué à vrai, même si
 * boolean vaut '0'.
 * Et puisque l'intéret d'avoir un type boolean est 
 * justement de se permettre d'utiliser ces conditions
 * implicites sans anxiété. */

#define MAX_LGNS 15
#define MAX_COLS MAX_LGNS
#define VECT_SIZE MAX_LGNS

#pragma region Prototypes
void menu(short *array1, short *array2, short *array3,
	  short *vect, const byte size);

int r_rand(const int min, const int max);
short ask_val(const short min, const short max, char *text);

void map_simple(short *array, const byte nbLn, const byte nbCol,
		void (*action)(short *cell), const bool newLine);
void map_double(const short *arraySource, short *arrayDest, const byte size,
		short (*action)(const short cell, const short arg),
		const short action_arg);
void map_triple(const short *array1, const short *array2, short *arrayDest,
		const byte size, short (*action)(const short cell1, const short cell2));
void map_cross(const short *array1, const short *array2, short *vectDest,
	       const byte size,
	       short (*action)(const short *array1Line, const short *array2Col, const byte size));

void random_cell(short *cellule);
void init_array(short *array, const byte size);

void show_cell(short *cell);
void show_array(short *array, const byte nbLgn, const byte nbCol,
		const char *title);

short add_to_cell(const short cell, const short val);
void add_to_array(const short *arraySource, short *arrayDest,
		   const byte size);
void soustract_to_array(const short *arraySource, short *arrayDest,
			 const byte size);
			 
short mutl_cell(const short cell, const short val);
void mult_to_array(const short *arraySource, short *arrayDest,
		    const byte size);

short add_cells(const short cell1, const short cell2);
void add_arrays(const short *array1, const short *array2,
		 short *arrayDest, const byte size);

short soustract_cells(const short cell1, const short cell2);
void soustract_arrays(const short *array1, const short *array2,
		       short *arrayDest, const byte size);

short cross_mult(const short *array1Line, const short *array2Col,
		 const byte size);
void cross_arrays(const short *array1, const short *array2,
		  short *vectDest, const byte size);
#pragma endregion

#pragma region Main
int main(void)
{
	short array1[MAX_LGNS][MAX_COLS],
	      array2[MAX_LGNS][MAX_COLS],
	      array3[MAX_LGNS][MAX_COLS],
	      vect[VECT_SIZE];
	byte size;

	size = (byte) ask_val(0, MAX_LGNS,
		"Quelle taille de tableau souhaitez-vous utiliser?");
	
	srand(time(NULL));
	init_array(&array1[0][0], size);
	init_array(&array2[0][0], size);

	show_array(&array1[0][0], size, size,
		   "Premier tableau");
	show_array(&array2[0][0], size, size,
		   "Second tableau");
	
	menu(&array1[0][0], &array2[0][0], &array3[0][0], vect, size);

	return 0;
}
#pragma endregion

#pragma region Menu
/* Affiche le menu et appelle les fonction selon le
 * choix de l'utilisateur. */
void menu(short *array1, short *array2, short *array3,
	  short *vect, const byte size)
{
	short choix;
	do {
		printf("Menu\n");
		printf("1. Ajouter une valeur à la première matrice\n");
		printf("2. Additionner les deux premières matrices\n");
		printf("3. Soustraire une valeur à la première matrice\n");
		printf("4. Soustraire les deux premières matrices\n");
		printf("5. Multiplier la première matrice par une valeur\n");
		printf("6. Mutliplier les deux premières matrices\n");
		printf("7. Quitter\n");

		printf("Votre choix: ");
		scanf("%hd", &choix);
	
		switch (choix) {
		case 1:
			add_to_array(array1, array3, size);
			break;
		case 2:
			add_arrays(array1, array2, array3, size);		
			break;
		case 3:
			soustract_to_array(array1, array3, size);
			break;
		case 4: 
			soustract_arrays(array1, array2, array3, size);
			break;
		case 5:
			mult_to_array(array1, array3, size);
			break;
		case 6:
			cross_arrays(array1, array2, vect, size);	
		}

	} while (choix != 7);
}
#pragma endregion

#pragma region Commons fonctions
/* Donne une valeur aléatoire entre min et max
 * (compris). */
int r_rand(const int min, const int max)
{
	return rand() % (max + 1) + min;
}

/* Demande une valeur à l'utilisateur et vérifie
 * qu'elle se situe dans l'intervale [min, max].
 * text est le texte qui va être affiché à
 * l'utilisateur lors de la saisie. */
short ask_val(const short min, const short max, char *text)
{
        short val;

        do {
                printf("%s [%hd, %hd] ", text, min, max);

                scanf("%hd", &val);
        } while (val < min || val > max);

        return val;
}
#pragma endregion

#pragma region High-Order Functions
/* Fonction d'ordre supérieur.
 * Exécute action pour chaque cellule du tableau tel qu'il
 * est défini par nbLgn et nbCol.
 * (Equivalent à la fonction map que l'on trouve dans les
 * langages fonctionnels)
 * Peut légèrement ralentir l'éxécution, mais ça n'a pas
 * trop d'importance ici (et puis c'est plus amusant à utiliser).
 * Le premier argument de action correspond au pointeur 
 * de la cellule itérée.
 * newLine indique si un retour à la ligne doit être affiché
 * à chaque nouvelle ligne.
 * Utilisée à l'affichage et à l'initialisation des tableaux. */
void map_simple(short *array, const byte nbLn, const byte nbCol,
		void (*action)(short *cell), const bool newLine)
{
        byte iLn, iCol;

	/* Reste de colonnes pour terminer les lignes */
	const byte colsRemains = (MAX_COLS - nbCol);

        for (iLn = 0; iLn < nbLn; iLn++) {
                for (iCol = 0; iCol < nbCol; iCol++, array++)
                        (*action)(array);

		/* Pas très subtil, mais il faudrait écrire une
		 * nouvelle fonction map pour afficher
		 * le tableau sinon */
		if (newLine)
			printf("\n");

                array += colsRemains;
        }
}

/* Fonction d'ordre supérieur.
 * Identique à map_simple, mais parcourt deux tableaux
 * simultanément et permet de stocker le traitement 
 * retourné par action sur une cellule de arraySource
 * dans la cellule correspondante de arrayDest.
 * Ainsi, action doit retourner la valeur à enregistrer
 * dans arrayDest.
 * Puisque le C ne permet pas le currying, on est obligé
 * de faire passer les arguments d'action via action_arg.
 * Utilisé par les opérations scalaires */
void map_double(const short *arraySource, short *arrayDest, const byte size,
		short (*action)(const short cell, const short arg),
		const short action_arg)
{
	byte iLn, iCol;

	/* Reste de colonnes pour terminer les lignes */
        const byte colsRemains = (MAX_COLS - size);

        for (iLn = 0; iLn < size; iLn++) {
                for (iCol = 0; iCol < size; iCol++) {
                        *arrayDest = (*action)(*arraySource, action_arg);
			
			arraySource++;
			arrayDest++;
		}

                arraySource += colsRemains;
		arrayDest += colsRemains;
        }
}

/* Fonction d'ordre supérieur.
 * Identique à map_simple, mais parcourt trois tableaux
 * simultanément et permet de stocker le traitement
 * retourné par action sur une cellule de array1 et
 * de array2 dans la cellule correspondante de arrayDest.
 * Ainsi, action doit retourner la valeur à enregistrer
 * dans arrayDest.
 * Utilisé dans les opérations matricielles simples. */
void map_triple(const short *array1, const short *array2, short *arrayDest,
		const byte size, short (*action)(const short cell1, const short cell2))
{
        byte iLn, iCol;

        /* Reste de colonnes pour terminer les lignes */
        const byte colsRemains = (MAX_COLS - size);

        for (iLn = 0; iLn < size; iLn++) {
                for (iCol = 0; iCol < size; iCol++) {
                        *arrayDest = (*action)(*array1, *array2);
			
			array1++;
			array2++;
			arrayDest++;
		}
		
                array1 += colsRemains;
		array2 += colsRemains;
                arrayDest += colsRemains;
        }
}

/* Fonction d'ordre suprérieur.
 * Parcourt array1 en lignes et array2 en colonnes.
 * Pour chaque ligne/colonne, appel action avec le
 * pointeur de la première cellule de la ligne et
 * de la colonne.
 * Le résultat de chaque appel à action est enregistré
 * dans vectDest.
 * Utilisé dans le pseudo-produit matriciel. */
void map_cross(const short *array1, const short *array2, short *vectDest,
	       const byte size,
	       short (*action)(const short *array1Line, const short *array2Col, const byte size))
{
        byte i;

        for (i = 0; i < size; i++) {
		*vectDest = (*action)(array1, array2, size);

                array1 += MAX_COLS;
                array2++;
		vectDest++;
        }
}
#pragma endregion

#pragma region Initialise array
/* Rempli la cellule aléatoirement par une valeur entre
 * 0 et 10 (compris) */
void random_cell(short *cellule)
{
	*cellule = (short) r_rand(0, 10);
}
/* Initialise le tableau array avec des valeurs aléatoires
 * entre 0 et 10 dans la partie définie par size. */
void init_array(short *array, const byte size)
{
	map_simple(array, size, size, random_cell, false);
}
#pragma endregion

#pragma region Show arrays content
/* Affiche le contenu d'une cellule */
void show_cell(short *cell)
{
	printf("%hd\t", *cell);
}
/* Affiche le contenu du tableau array dans sa partie
 * définie par size.
 * L'argument title est le titre qui sera affiché en haut du tableau */
void show_array(short *array, const byte nbLgn, const byte nbCol,
		const char *title)
{
	printf("%s:\n", title);
                                                   
        map_simple(array, nbLgn, nbCol, show_cell, nbCol > 1);

	/* Pas réellement nécéssaire, mais plus agréable visuellement */
	printf("\n");
}
#pragma endregion

#pragma region Scalar operations
/* Retourne le contenu de cell augmenté de val */
short add_to_cell(const short cell, const short val)
{
	return cell + val;
}
/* Demande une valeur à l'utilisateur, l'additionne à 
 * toutes les valeurs de arraySource et enregistre
 * le résultat dans arrayDest.
 * Affiche arrayDest. */
void add_to_array(const short *arraySource, short *arrayDest,
		   const byte size)
{
	short val =
		ask_val(SHRT_MIN, SHRT_MAX,
        	        "Quel valeur souhaitez-vous ajouter aux "
                        "cellules du tableau ?");

	map_double(arraySource, arrayDest, size, add_to_cell, val);

	show_array(arrayDest, size, size, "Résultat");
}

/* Demande une valeur à l'utilisateur, la soustrait à
 * toutes les valeurs de arraySource et enregistre
 * le résultat dans arrayDest.
 * Affiche arrayDest. */
void soustract_to_array(const short *arraySource, short *arrayDest,
			 const byte size)
{
        short val =
                ask_val(-(SHRT_MAX + 1), -(SHRT_MIN + 1),
                        "Quel valeur souhaitez-vous soustraire aux "
                        "cellules du tableau ?");

	/* Revient au même que d'ajouter l'opposé */
        map_double(arraySource, arrayDest, size, add_to_cell, -val);

        show_array(arrayDest, size, size, "Résultat");
}

/* Retourne le contenu de cell multiplié par val */
short mutl_cell(const short cell, const short val)
{
        return cell * val;
}
/* Demande une valeur à l'utilisateur, la multiplie à
 * toutes les valeurs de arraySource et enregistre
 * le résultat dans arrayDest.
 * Affiche arrayDest. */
void mult_to_array(const short *arraySource, short *arrayDest,
		    const byte size)
{
        short val =
                ask_val(SHRT_MIN, SHRT_MAX,
                        "Quel valeur souhaitez-vous multipliser "
                        "cellules du tableau ?");

        map_double(arraySource, arrayDest, size, mutl_cell, val);

        show_array(arrayDest, size, size, "Résultat");
}
#pragma endregion

#pragma region Simple matrix operations
/* Additione le contenu de deux cellules et retourne le résultat */ 
short add_cells(const short cell1, const short cell2)
{
	return cell1 + cell2;
}
/* Additionne le contenu de array1 avec array2 et stocke le
 * résultat dans arrayDest.
 * Affiche arrayDest. */
void add_arrays(const short *array1, const short *array2,
		 short *arrayDest, const byte size)
{
        map_triple(array1, array2, arrayDest, size, add_cells);

        show_array(arrayDest, size, size, "Résultat");
}

/* Soustrait le contenu de deux cellules et retourne le résultat */
short soustract_cells(const short cell1, const short cell2)
{
        return cell1 - cell2;
}
/* Soustrait le contenu de array1 avec array2 et stocke le
 * résultat dans arrayDest.
 * Affiche arrayDest. */
void soustract_arrays(const short *array1, const short *array2,
		       short *arrayDest, const byte size)
{
        map_triple(array1, array2, arrayDest, size, soustract_cells);

        show_array(arrayDest, size, size, "Résultat");
}
#pragma endregion

/* Rmks: 
 * L'ensemble des fonctions sur les opérations scalaires
 * et matricielles simples pourraient êtres ré-écrites
 * sur une seule et unique fonction si le C possédait
 * les expressions Lambda. Dommage. */

#pragma region Cross multiplication
/* Renvoie la somme des produits des cellules
 * de la ligne de array1 par les colonnes de array2. */
short cross_mult(const short *array1Line, const short *array2Col,
		 const byte size)
{
	byte i;
	short sum = 0;

	for (i = 0; i < size; i++) {
		sum += *array1Line * *array2Col;
		array1Line++;
		array2Col += MAX_COLS; 
	}
	return sum;
}
/* Effectue un pseudo-produit matriciel en calulant,
 * dans vectDest la somme des produits des lignes de
 * array1 par les colonnes de array2. */
void cross_arrays(const short *array1, const short *array2,
		  short *vectDest, const byte size)
{
	map_cross(array1, array2, vectDest, size, cross_mult);

	show_array(vectDest, 1, size, "Résultat");
}
#pragma endregion

