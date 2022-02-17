#include <stdio.h>

#define PI 3.14

int main()
{
    int rayon;
    float circonference, aire;
    circonference = aire = 0;

    printf("Entrez le rayon du cercle \n:");
    scanf("%d", &rayon);
    circonference = 2 * PI * rayon;
    aire = PI * (rayon * rayon);
    printf("La circonference vaut %.2f et l'aire vaut %.2f\n", circonference, aire);

    return 0;

}
