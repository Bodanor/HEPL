#ifdef DATAH

#else


#define DATAH
#include <time.h>
// 2022 , interdit de modifier les champs existants

struct VehiculeBG { 
         int  Supprime ;
         int  Reference ;
	 char Constructeur[30] ;
   	 char Modele[30] ;
	 int  Quantite ;
	 int cylindree ;
      
	} ;

struct FactureBG
       {
         int NumeroFacturation ;
         char Acheteur[60] ;
	 time_t DateFacturation ;
         int Quantite;
	 int Reference ;
	 int Cylindree;
	
	} ;  	
#endif
