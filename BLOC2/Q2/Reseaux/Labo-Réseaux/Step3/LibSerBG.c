#include "LibSerBG.h"

void AProposServeurHV(char *Version,char *Nom1,char* Nom2)
{
 printf("Version : %s \n",Version ) ;
 printf("Nom1 : %s \n",Nom1 ) ;
 printf("Nom2 : %s \n",Nom2 ) ;
}


int RechercheBG(char * NomFichier, int ref, struct VehiculeBG *Unrecord)
{
    
    int nbr;
    FILE * test;

    test=fopen(NomFichier,"r");
    if(test ==NULL)
    {
        fprintf(stderr,"Echec Ouverture\n");
        exit(0);
    }
    else
    {
        fprintf(stderr,"Ouverture reussie\n");
    }

    fseek(test,0,SEEK_SET);
    fread(Unrecord,sizeof(struct VehiculeBG),1,test);

    while (!feof(test) && Unrecord->Reference != ref)
    {
        fread(Unrecord,sizeof(struct VehiculeBG),1,test);
    }


    if(Unrecord->Reference!= ref)
        return 0;
    else
        return 1;
    

    fclose(test);



}