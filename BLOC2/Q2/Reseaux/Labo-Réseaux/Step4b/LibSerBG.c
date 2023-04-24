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


int ReservationBG(char* NomFichier,int Reference ,int Quantite ) 
{
     FILE * test;
    int nbr,quantite;
    test=fopen(NomFichier,"r+");
    struct VehiculeBG Unrecord;
    
    
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
    fread(&Unrecord,sizeof(struct VehiculeBG),1,test);

    while (!feof(test) && Unrecord.Reference != Reference)
    {
        fread(&Unrecord,sizeof(struct VehiculeBG),1,test);
    }


    if(Unrecord.Reference!= Reference)
    {
        fclose(test);
        return -1;
    }    
    else
    {
        if(Unrecord.Quantite>=Quantite)
        {
            Unrecord.Quantite=Unrecord.Quantite-Quantite;
            
            fseek(test,-sizeof(struct VehiculeBG),SEEK_CUR);
            fwrite(&Unrecord,sizeof(struct VehiculeBG),1,test);
            fclose(test);
            return Unrecord.cylindree;
            
        }
        else
        {
            fclose(test);
            return 0;
        }
    
    }
    fclose(test);


}
int FacturationBG(char NomFichier[80], char NomClient[60], time_t date,int Quantite,int Reference,int Cylindree) 
{
     FILE * test;
    int nbr,quantite;
    test=fopen(NomFichier,"ab");
    struct FactureBG temp;
   int numero=1;
    
    if(test ==NULL)
    {
        fprintf(stderr,"Echec Ouverture\n");
        exit(0);
    }
    else
    {
        fprintf(stderr,"Ouverture reussie\n");
    }

    
    fseek(test,0,SEEK_END);
    numero=ftell(test)/sizeof(struct FactureBG);
    numero++;
   

    strcpy(temp.Acheteur,NomClient);
    temp.Quantite=Quantite;
    temp.Reference=Reference;
    temp.Cylindree=Cylindree;
    temp.DateFacturation=date;
    temp.NumeroFacturation=numero;
    

    int retour;


    retour=fwrite(&temp,sizeof(struct FactureBG),1,test);

    //fseek(test,-sizeof(struct FactureBG),SEEK_CUR);
    
    

    fclose(test);
    
    printf("%d",retour);


    return temp.NumeroFacturation;

}