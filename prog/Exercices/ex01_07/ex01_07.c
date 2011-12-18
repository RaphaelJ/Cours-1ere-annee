#include <stdio.h>
#include <stdlib.h>

float CelciusToFahr(float celcius)
{
	return 32 + (celcius * 9 / 5);  
}

int main(void) 
{
	float celcius;

	printf("Degres Celcius: ");
	scanf("%f", &celcius);

	printf("%.2f C = %.2f F\n",
		celcius,
		CelciusToFahr(celcius));

	return 0;
}
