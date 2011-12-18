#include <stdio.h>

int main(void)
{
	int nb1 = 10,
		nb2 = 20
		nb_temp;

	printf("Nb1 vaut %d et nb2 vaut %d\n", nb1, nb2);

	nb_temp = nb1;
	nb1 = nb2;
	nb2 = nb1;

	printf("Maintenant nb1 vaut %d et nb2 vaut %d\n", nb1, nb2);

	return 0;
}