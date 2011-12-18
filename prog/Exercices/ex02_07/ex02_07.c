#include <stdio.h>
#include <math.h>

int main (void) 
{
	float a, b ,c;
	double delta, delta_sqrt, cplx1, cplx2;
	
	printf("Entrez une equation du second degre (ax2 + bx + c = 0)\n");
	
	printf("a = ");
	scanf("%f", &a);

	printf("b = ");
	scanf("%f", &b);

	printf("c = ");
	scanf("%f", &c);

	if (a == 0) /* Premier degre */
	{
		if (b != 0)
			printf("x = %4.2f\n",
				- c / b);
		else if (c == 0)
			printf("Equation indeterminee\n");
		else /* C != 0 */
			printf("Equation impossible\n");
	}
	else /* Second degre */
	{
		delta = pow(b, 2) - 4 * a * c;

		if (delta > 0) /* 2 inconnues */
		{
			delta_sqrt = sqrt(delta);

			printf("x = %3.2f\n%9.2f\n",
				(-b + delta_sqrt) / (2 * a),
				(-b - delta_sqrt) / (2 * a));
		}
		else if (delta == 0) /* Une inconnue */
		{
			printf("x = %4.2f\n",
				- b / (2 * a));
		}
		else /* Immaginaire */
		{
			delta_sqrt = sqrt(- delta); /* SQRT(ABS(delta)) */

			cplx1 = - b / (2 * a);
			cplx2 = delta_sqrt / (2 * a);

			printf("x = %3.2f + %3.2f i\n",
				cplx1, cplx2);

			printf("%9.2f - %3.2f i\n",
				cplx1, cplx2);
		}
	}

	return 0;
}
