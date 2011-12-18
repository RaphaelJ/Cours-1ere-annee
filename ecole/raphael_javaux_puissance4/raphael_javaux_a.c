/* Raphael Javaux - 2104
 * Puissance 4
 * Version A (pointeurs) */

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

typedef char bool;
#define true 1
#define false 0

#define NB_LIGNES 6
#define NB_COLS 7

#define MAX_ALIGNES 4

/* Défini une case et ses différents états */
typedef enum _CASE {
	/* On peut directement utiliser les
	 * valeurs entières des caractères,
	 * et donc afficher dirrectement
	 * le contenu d'une case */
	VIDE = ' ',
	J1 = 'X',
	J2 = 'O'
} CASE;

/* Position d'un pion */
typedef struct _POSITION {
	short col;
	short lgn;
} POSITION;

/* Donne le joueur du tour suivant : */
#define Suivant(J) (J == J1 ? J2 : J1)

#ifdef WIN32
	#define ClearScreen() system("clrscr")
#else /* Unices et autres */
	#define ClearScreen() system("clear")
#endif

/* Donne la valeur d'une case du tableau : */
#define Case(l, c) *(tableau + (l * NB_COLS) + c)
#define CaseParPosition(position) Case(position.lgn, position.col)

void Puissance4();

CASE TourRand();

void ViderTableau(CASE *tableau);
void AfficherTableau(const CASE *tableau, const CASE tour);

short LigneLibre(const CASE *tableau, const short colonne);
POSITION DemanderCase(CASE *tableau, const CASE tour);

short NbAlignes(const CASE *tableau, const CASE tour, const POSITION case_jouee,
	short deltaX, short deltaY);
short MaxAlignes(const CASE *tableau, const CASE tour, const POSITION case_jouee);

int main(void)
{
	char continuer;

	srand(time(NULL));

	do {
		Puissance4();

		printf("Recommencer [O/n]: ");

		#ifdef WIN32
			fflush(stdin);
		#endif
		continuer = getchar();
	} while (continuer != 'n');
	
	return 0;
}


/* Ne demande rien, ne renvoie rien, mais fait tout */
void Puissance4()
{
	CASE tableau[NB_LIGNES][NB_COLS],
	     tour = TourRand(); /* Joueur qui commence  */
	short coups = 0,
	      combo = 0;
	POSITION case_jouee;

	ViderTableau(&tableau[0][0]);

	while (combo < MAX_ALIGNES && coups < NB_LIGNES * NB_COLS) {
		AfficherTableau(&tableau[0][0], tour);

		case_jouee = DemanderCase(&tableau[0][0], tour);
	
		combo = MaxAlignes(&tableau[0][0], tour, case_jouee);

		tour = Suivant(tour);
		coups++;
	}

	AfficherTableau(&tableau[0][0], VIDE);

	if (combo == MAX_ALIGNES) {
		if (Suivant(tour) == J1)
			printf("Joueur 1 gagne la partie\n");
		else
			printf("Joueur 2 gagne la partie\n");
	} else
		printf("Egalite\n");
}

/* Renvoie J1 ou J2, aléatoirement.
 * Utilisé pour le choix du premier joueur.
 *
 * Sortie: Case valant J1 ou J2, aléatoirement. */
CASE TourRand()
{
	return (rand() % 2) == 0 ? J1 : J2;
}

/* Initialise un tableau de celulles vides et le retourne
 *
 * @tableau: Tableau à remplir de cases vides. */
void ViderTableau(CASE *tableau)
{
	short lgn, col;
	const CASE val = VIDE; /* Valeur par défaut des cellules */

	for (lgn = 0; lgn < NB_LIGNES; lgn++) {
		for (col = 0; col < NB_COLS; col++)
			Case(lgn, col) = val;
	}
}

/* Affiche l'ensemble du tableau.
 *
 * @tableau: tableau de jeu ;
 * @tour: Joueur en train de jouer. */
void AfficherTableau(const CASE *tableau, const CASE tour)
{
	short i, j;

	ClearScreen();

	/* En-tête */
	for (j = 1; j <= NB_COLS; j++)
		printf("%hd\t", j);
	printf("\n");
	
	/* Tableau */
	for (i = 0; i < NB_LIGNES; i++) {
		for (j = 0; j < NB_COLS; j++)
			printf("%c\t", Case(i, j));

		printf("\n");
	}

	printf("\n");

	/* Légende */
	printf("%c Joueur 1 :\t%c\n",
		tour == J1 ? '>' : ' ', J1);
	printf("%c Joueur 2 :\t%c\n",
		tour == J2 ? '>' : ' ', J2);
}

/* Renvoie la ligne libre du tableau pour la colonne donnée.
 * Renvoie -1 si aucune case n'est libre.
 * Compte les lignes à partir de 0 de haut en bas.
 * 
 * @tableau: Tableau de jeu ;
 * @colonne: Colonne à jouer.
 *
 * Sortie: La ligne libre, en comptant depuis 0 en haut. -1 si pas
 *	de case libre. */
short LigneLibre(const CASE *tableau, const short colonne)
{
	short lgn;
	for (lgn = NB_LIGNES - 1; lgn >= 0; lgn--) {
		if (Case(lgn, colonne) == VIDE)
			return lgn;
	}
	return -1;
}

/* Demande une case à jouer à l'utilisateur.
 * Vérifie si la colonne peut être jouée et *AJOUTE* le pion.
 *
 * @tableau: Tableau de jeu ;
 * @tour: Joueur en cours.
 * 
 * Sortie: Position du pion joué. */
POSITION DemanderCase(CASE *tableau, const CASE tour)
{
	POSITION pion;

	do {
		printf("Colonne a jouer [1~%d] : ", NB_COLS);
		scanf("%hd", &(pion.col));
		getchar(); /* Unices */

		pion.col--; /* Décale pour commencer à 0 */
	} while (pion.col < 0 || pion.col >= NB_COLS
		|| (pion.lgn = LigneLibre(tableau, pion.col)) < 0);

	CaseParPosition(pion) = tour;
	
	return pion;
}

/* Retourne ne nombre de pions alignés autour de case_jouee,
 * par rapport à un déplacement horizontal et/ou vertical.
 * Essaye également en inversant le déplacement en repartant
 * de la case jouée (i.e. vers la droite, puis vers la gauche).
 * 
 * @tableau: Tableau de jeu ;
 * @tour: Joueur en cours (alignement à vérifier) ;
 * @position: Position du pion joué ;
 * @deltaX: Déplacement horizontal ;
 * @deltaY: Déplacement vertical.
 * 
 * Sortie: Le nombre de pions alignés. */
short NbAlignes(const CASE *tableau, const CASE tour,
	const POSITION case_jouee, short deltaX, short deltaY)
{
	POSITION case_tmp;
	short i,
	      nb = 1; /* Ne vérifie pas la première case */
	      
	for (i = 0; i < 2; i++) { /* Effectue le déplacement dans les deux sens */
		case_tmp.col = case_jouee.col + deltaX;
		case_tmp.lgn = case_jouee.lgn + deltaY;
	
		for (case_tmp; case_tmp.col >= 0 && case_tmp.col < NB_COLS
			       && case_tmp.lgn >= 0 && case_tmp.lgn < NB_LIGNES
			       && CaseParPosition(case_tmp) == tour;
		     case_tmp.col += deltaX, case_tmp.lgn += deltaY)
				nb++;
		
		/* Change de sens */
		deltaX *= -1;
		deltaY *= -1;
	}

	return nb;
}

/* Retourne le nombre maximal de pions alignés autour de
 * case_jouee.
 * Rmks: Ne vérifie pas si le pion case_jouee est correctement
 * 	placé. Ca permet de vérifier le nombre de pions alignés
 *	lorsque le pion n'est pas encore joué (pour l'IA).
 * 
 * @tableau: Tableau de jeu ;
 * @tour: Joueur en cours (alignement à vérifier) ;
 * @position: Position du pion joué.
 * 
 * Sortie: Le nombre maximal de pions alignés. */
short MaxAlignes(const CASE *tableau, const CASE tour,
	const POSITION case_jouee)
{
	short max, val;

	max = NbAlignes(tableau, tour, case_jouee, 1, 0); /* Horizontal */

	if (max < MAX_ALIGNES
		&& (val = NbAlignes(tableau, tour, case_jouee, 0, 1)) > max) /* Vertical */
		max = val;
	else if (max < MAX_ALIGNES
		&& (val = NbAlignes(tableau, tour, case_jouee, 1, 1)) > max) /* Diagonale desc. */
		max = val;
	else if (max < MAX_ALIGNES
		&& (val = NbAlignes(tableau, tour, case_jouee, 1, -1)) > max) /* Diagonale asc. */
		max = val;

	return max;
}
