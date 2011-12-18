#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYS_SIZE 15

int r_rand(int min, int max); /* Retoure un nombre aléatoire compris entre min et max */
void show_tab(short *p_tab, short size, short dim); /* Affiche un tableau ou un vecteur */
void operate_val_to_tab(short *original, /* Effectue une opération sur une valeur à un tableau */
				    short *result, short size, int val, char calc_operator);
void operate_on_tabs(short *tab1, short *tab2, /* Effectue une opération sur deux matrices */
			  short *result, short size, char calc_operator);
void produit_mat(short *tab1, short *tab2, /* Effectue un produit matriciel et enregistre dans result */
				 short *result, short size);

/* Demande a l'utilisateur une valeur a ajouter à une matrice */
void action_add_val(short *tab, short *result, short size);
/* Affiche la somme de deux matrices */
void action_add(short *tab1, short *tab2, short *result, short size);

/* Demande a l'utilisateur une valeur a soustraire à une matrice */
void action_soustract_val(short *tab, short *result, short size);
/* Affiche la soustraction de deux matrices */
void action_soustract(short *tab1, short *tab2, short *result, short size);

/* Demande a l'utilisateur une valeur a multiplier à une matrice */
void action_mult_val(short *tab, short *result, short size);

/* Effectue un produit matriciel et enregistre dans result */
void action_produit_mat(short *tab1, short *tab2, short *result, short size);

int main(void) 
{
	char choix_menu = 0;
	short size, row, col,
		vect[ARRAYS_SIZE],
		tab1[ARRAYS_SIZE][ARRAYS_SIZE],
		tab2[ARRAYS_SIZE][ARRAYS_SIZE],
		tab3[ARRAYS_SIZE][ARRAYS_SIZE];

	srand(time(NULL));

	printf("Taille du tableau: ");
	scanf("%d", &size);

	size = size > ARRAYS_SIZE ? ARRAYS_SIZE : size;

	for(row = 0; row < size; row++) 
	{
		for(col = 0; col < size; col++) 
		{
			tab1[row][col] = r_rand(0, 10);
			tab2[row][col] = r_rand(0, 10);
		}	
	}

	printf("== Premier tableau ==\n");
	show_tab(&tab1[0][0], size, 2);

	printf("== Deuxieme tableau ==\n");
	show_tab(&tab2[0][0], size, 2);

	while (1) 
	{
		printf("== Menu ==\n");
		printf("1. Additioner une valeur au premier tableau\n");
		printf("2. Additioner les deux premiers tableaux\n");
		printf("3. Soustraire une valeur au premier tableau\n");
		printf("4. Soustraire les deux premiers tableaux\n");
		printf("5. Multiplier une valeur au premier tableau\n");
		printf("6. Multiplier les deux premiers tableaux\n");
		printf("Autre. Sortie\n");

		printf("> ");
		scanf("%d", &choix_menu);

		switch (choix_menu) {
		case 1:
			action_add_val(&tab1[0][0], &tab3[0][0], size);
			break;
		case 2:
			action_add(&tab1[0][0], &tab2[0][0], &tab3[0][0], size);
			break;
		case 3:
			action_soustract_val(&tab1[0][0], &tab3[0][0], size);
			break;
		case 4:
			action_soustract(&tab1[0][0], &tab2[0][0], &tab3[0][0], size);
			break;
		case 5:
			action_mult_val(&tab1[0][0], &tab3[0][0], size);
			break;
		case 6:
			action_produit_mat(&tab1[0][0], &tab2[0][0], &vect[0], size);
			break;
		default:
			return 0;
		}

		printf("\n");
	}
}

int r_rand(int min, int max) /* Retoure un nombre aléatoire compris entre min et max (inclus) */
{
	return (int) (rand() % (max - min +  1) + min);
}

void show_tab(short *p_tab, short size, short dim) /* Affiche un tableau */
{
	short col, row;

	for(row = 0; row < size; row++) 
	{
		if (dim > 1)
		{
			for(col = 0; col < ARRAYS_SIZE; col++)
			{
				if (col < size)
					printf("%4d ", *p_tab);
	
				p_tab++;
			}

			printf("\n");
		}
		else /* Vecteur */
		{
			printf("%4d", *p_tab);
			p_tab++;
		}
	}
}

void operate_val_to_tab(short *original, short *result, short size, int val, char calc_operator) 
{
	short col, row;

	for(row = 0; row < size; row++) 
	{
		for(col = 0; col < ARRAYS_SIZE; col++)
		{
			if (col < size)
			{
				switch (calc_operator) {
				case '+':
					*result = *original + val;
					break;
				case '-':
					*result = *original - val;
					break;
				case '*':
					*result = *original * val;
				}
			}

			original++;
			result++;
		}
	}
}

void operate_on_tabs(short *tab1, short *tab2, short *result, short size, char calc_operator) 
{
	short col, row;

	for(row = 0; row < size; row++) 
	{
		for(col = 0; col < ARRAYS_SIZE; col++)
		{
			if (col < size)
			{
				switch (calc_operator) {
				case '+':
					*result = *tab1 + *tab2;
					break;
				case '-':
					*result = *tab1 - *tab2;
					break;
				case '*':
					*result = *tab1 * *tab2;
				}
			}
				

			tab1++;
			tab2++;
			result++;
		}
	}
}

void produit_mat(short *tab1, short *tab2, short *result, short size)
{
	short col, row;

	for(row = 0; row < size; row++) 
	{
		*result = 0;
		for(col = 0; col < ARRAYS_SIZE; col++)
		{
			if (col == row && col < size)
				*result += *tab1 * *tab2;

			tab1++;
			tab2++;
		}
		result++;
	}
}

void action_add_val(short *tab, short *result, short size)
{
	int val_to_add;

	printf("Quelle valeur souhaitez-vous ajouter ? ");
	scanf("%d", &val_to_add);

	operate_val_to_tab(tab, result, size, val_to_add, '+');
	
	printf("== Resultat ==\n");
	show_tab(result, size, 2);
}

void action_add(short *tab1, short *tab2, short *result, short size)
{
	
	operate_on_tabs(tab1, tab2, result, size, '+');

	printf("== Resultat ==\n");
	show_tab(result, size, 2);
}

void action_soustract_val(short *tab, short *result, short size)
{
	int val_to_soustract;

	printf("Quelle valeur souhaitez-vous soustraire ? ");
	scanf("%d", &val_to_soustract);

	operate_val_to_tab(tab, result, size, -val_to_soustract, '-');
	
	printf("== Resultat ==\n");
	show_tab(result, size, 2);
}

void action_soustract(short *tab1, short *tab2, short *result, short size)
{
	
	operate_on_tabs(tab1, tab2, result, size, '-');

	printf("== Resultat ==\n");
	show_tab(result, size, 2);
}

void action_mult_val(short *tab, short *result, short size)
{
	int mult;

	printf("Quelle valeur souhaitez-vous multiplier a la matrice ? ");
	scanf("%d", &mult);

	operate_val_to_tab(tab, result, size, mult, '*');
	
	printf("== Resultat ==\n");
	show_tab(result, size, 2);
}

void action_produit_mat(short *tab1, short *tab2, short *result, short size)
{
	produit_mat(tab1, tab2, result, size);
	
	printf("== Resultat ==\n");
	show_tab(result, size, 1);
}
