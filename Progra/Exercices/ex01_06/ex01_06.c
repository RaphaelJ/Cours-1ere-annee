#include <stdio.h>
#include <stdlib.h>

float FarhToCelcius(float fahrenheit)
{
	return 5 * (fahrenheit -  32) / 9;  
}

int main(void) 
{
	float fahrenheit;

	printf("Degres fahrenheit: ");
	scanf("%f", &fahrenheit);

	printf("%.2f F = %.2f C\n",
		fahrenheit,
		FarhToCelcius(fahrenheit));

	return 0;
}
