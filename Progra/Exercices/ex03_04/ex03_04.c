#include <stdio.h>

int main (void) 
{
	int nb_nbre,
		curr_nbre = 0,
		old_nbre = 1,
		new_nbre = 0,
		tmp;

	printf("Combien de nombres souhaitez-vous: ");
	scanf("%d", &nb_nbre);

	printf("== Suite de Fibonacci ==\n");

	while (curr_nbre++ < nb_nbre)
	{
		printf("%4d:%6d\n",
			curr_nbre,
			new_nbre);

		tmp = new_nbre;
		new_nbre += old_nbre;
		old_nbre = tmp;
	}
}