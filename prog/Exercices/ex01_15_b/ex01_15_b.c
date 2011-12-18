#include <stdio.h>

int main(void)
{
	int nb1 = 10,
		nb2 = 20;

	printf("Nb1 vaut %d et nb2 vaut %d\n", nb1, nb2);


	nb1 = nb2 + nb1;
	nb2 = nb1 - nb2;
	nb1 = nb1 - nb2;

	printf("Maintenant nb1 vaut %d et nb2 vaut %d\n", nb1, nb2);

	return 0;
}