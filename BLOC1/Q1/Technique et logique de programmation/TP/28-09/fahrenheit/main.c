#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fahr;
    float celcius = 0;

    printf("Entrez un entier en fahrenheit \n:");
    scanf("%d", &fahr);

    celcius = (fahr - 32) * (5.0 / 9.0);
    printf("%d fahrenheit = %.1f celcius\n", fahr, celcius);
}
