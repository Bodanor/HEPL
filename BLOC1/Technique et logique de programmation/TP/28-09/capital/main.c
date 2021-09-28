#include <stdio.h>
#include <stdlib.h>

int main()
{
    int capital_depart, taux_interet;
    float interret_obtenu;

    capital_depart = interret_obtenu = taux_interet = 0;
    printf("Entrez le capital de depart \n:");
    scanf("%d", &capital_depart);
    printf("Entrez le taux d'interets \n:");
    scanf("%d", &taux_interet);

    interret_obtenu = (capital_depart / 100.0) * taux_interet;
    interret_obtenu += (float)capital_depart;
    printf("Interrets obtenu apres 1 an : %f\n", interret_obtenu);

    return 0;
}
