#include <stdio.h>
#include <stdlib.h>

int main()
{
    int cm = 0;
    float poids_f, poids_h;
    poids_f = poids_h = 0.0;

    printf("Entrez votre taille en cm \n:");
    scanf("%d", &cm);
    poids_h = ((float)cm - 100) - ((float)cm - 150) / 4;
    poids_f = (poids_h / 100) * 92;
    poids_f = poids_h - poids_f;

    printf("poids ideal pour un homme : %.1f et pour une femme %.1f\n", poids_h, poids_f);

    return 0;


}
