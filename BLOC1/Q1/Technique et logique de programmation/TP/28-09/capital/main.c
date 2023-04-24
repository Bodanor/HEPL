#include <stdio.h>
#include <stdlib.h>

int main()
{
    int capital_depart, taux_interet;
    float interet_obtenu;

    capital_depart = interet_obtenu = taux_interet = 0;
    printf("Entrez le capital de depart \n:");
    scanf("%d", &capital_depart);
    printf("Entrez le taux d'interet \n:");
    scanf("%d", &taux_interet);

    interet_obtenu = (capital_depart / 100.0) * taux_interet;
    interet_obtenu += (float)capital_depart;
    printf("Interrets obtenu apres 1 an : %f\n", interet_obtenu);

    return 0;
}
