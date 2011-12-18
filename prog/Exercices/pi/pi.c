#include <stdio.h>
#include <math.h>

int main (void) /* Calcule les décimales de PI */
{
	char signe = 1;
	int decimale = 0,
		pi_int,
		old_pi_int,
		diviseur = 1;
		
	double pi = 0,
		old_pi = 0;

	while (1)
	{
		pi += signe * (1.0 / diviseur);
		diviseur += 2;
		
		pi_int = (int) (pi * pow(10, decimale) * 4);

		if (pi_int == old_pi_int) /* Nouvelle décimale */
		{
			printf("%.16 lf\n", pi * 4);
			decimale++;
		}

		old_pi_int = pi_int;

		signe *= -1;
	}
}