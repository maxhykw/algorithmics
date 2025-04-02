
#include <stdio.h>
#include <stdlib.h>

/*
Binôme 1 : Maxime HAYAKAWA IVANOVIC
Mail 1 : maxime.hayakawa-ivanovic@universite-paris-saclay.fr

Binôme 2 : Firdaous ELOUADI
Mail 2 : firdaous.elouadi@universite-paris-saclay.fr
*/




/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;


/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);



/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
}

/*************************************************/
/*                                               */
/*       UnPlusDeuxEgalTrois                     */
/*                                               */
/*************************************************/


bool UnPlusDeuxEgalTrois(Liste L)
{
    if (estVide(L))
        return TRUE;

    int elt1 = premier(L);

    if (estVide(suite(L)))
        return (elt1 + 0) == 0;    
        
    int elt2 = premier(suite(L)); 

    if (estVide(suite(suite(L))))
        return (elt1 + elt2) == 0;

    int elt3 = premier(suite(suite(L))); 

    return (elt1 + elt2) == elt3;
}


/*************************************************/
/*                                               */
/*                Croissante                     */
/*                                               */
/*************************************************/


bool Croissante(Liste L)
{
    if (estVide(L)) 
        return FALSE;

    while (suite(L) != NULL) 
    {
        if (premier(L) >= premier(suite(L)))
            return FALSE;
        L = suite(L);
    }
    return TRUE;
}


/*************************************************/
/*                                               */
/*       NombreMemePosition                      */
/*                                               */
/*************************************************/


int NombreMemePosition1(Liste L1, Liste L2)
{
    if (estVide(L1) || estVide(L2))
        return 0;
    else 
        if (premier(L1) == premier(L2))
            return 1 + NombreMemePosition1(suite(L1), suite(L2));
        else 
            return 0 + NombreMemePosition1(suite(L1), suite(L2));
}


int NombreMemePosition2(Liste L1, Liste L2)
{
    int cpt = 0;
    while (NOT estVide(L1) && NOT estVide(L2))
    {   
        if (premier(L1) == premier(L2))
            cpt++;
        L1 = suite(L1);
        L2 = suite(L2);
    }
    return cpt;
}


int NbMemePos3Aux(Liste L1, Liste L2, int cpt)
{
    if (estVide(L1) || estVide(L2))
        return cpt;
    else 
        if (premier(L1) == premier(L2)) {
            return NbMemePos3Aux(suite(L1), suite(L2), cpt+1);
        } else
            return NbMemePos3Aux(suite(L1), suite(L2), cpt);
}

int NombreMemePosition3(Liste L1, Liste L2) 
{
    return NbMemePos3Aux(L1, L2, 0);
}


void NbMemePos4Aux(Liste L1, Liste L2, int *cpt)
{
    if (estVide(L1) || estVide(L2))
        return;
    else 
        if (premier(L1) == premier(L2)) {
            (*cpt)++;
            NbMemePos4Aux(suite(L1), suite(L2), cpt);
        } else
            NbMemePos4Aux(suite(L1), suite(L2), cpt);
}

int NombreMemePosition4(Liste L1, Liste L2)
{
    int cpt = 0;
    NbMemePos4Aux(L1, L2, &cpt);
    return cpt;
}


/*************************************************/
/*                                               */
/*       FonctVireDernier                        */
/*                                               */
/*************************************************/


Liste VD1(Liste L1) 
{
    if (estVide(suite(L1)))
        return NULL;
    else
        return ajoute(premier(L1), VD1(suite(L1)));
}

Liste FonctVireDernier1(Liste L1) 
{
    if (estVide(L1))
        return NULL;

    return VD1(L1);
}


Liste FonctVireDernier2(Liste L1)
{
    if (estVide(L1) || estVide(suite(L1)))
        return NULL;
    
    Liste res = NULL;
    Liste *p = &res;

    while (NOT estVide(suite(L1)))
    {
        empile(premier(L1), p);
        p = &(**p).suivant;
        L1 = suite(L1);
    }

    return res;
}

/*************************************************/
/*                                               */
/*       AjouteDevantPremierZero                 */
/*                                               */
/*************************************************/


Liste AjouteDevantPremierZero(Liste *L, int x)
{
    if (estVide(*L) || premier(*L) == 0)
        empile(x, L);
    else
        AjouteDevantPremierZero(&(**L).suivant, x);
}


/*************************************************/
/*                                               */
/*       AjouteDevantDernierZero                 */
/*                                               */
/*************************************************/


// Récursif (avec argument inout)  
void AjouteDevantDernierZero1(Liste *L, int x, Liste *p)
{
    if (estVide(*L)) { 
        if (p == NULL)
            empile(x, L);
        else 
            empile(x, p);
    } else {
        if (premier(*L) == 0) 
            p = &(*L); // Va pointer vers le dernier endroit où se trouve un 0 (s'il y en a)
        AjouteDevantDernierZero1(&(**L).suivant, x, &(*p));
    }
}


void DernierBis(Liste *L, int x, Liste *p)
{
    if (estVide(*L)) { 
        if (p == NULL)
            empile(x, L);
        else 
            empile(x, p);
    } else {
        if (premier(*L) == 0) 
            p = &(*L); // Va pointer vers le dernier endroit où se trouve un 0 (s'il y en a)
        DernierBis(&(**L).suivant, x, &(*p));
    }
}

// Récursif terminal   
void AjouteDevantDernierZero2(Liste *L, int x)
{
   Liste *p = NULL;
   DernierBis(&(*L), x, &(*p));
}


// Itératif 
void AjouteDevantDernierZero3(Liste *L, int x)
{
    Liste *p = NULL;
    while (NOT estVide(*L))
    {
        if (premier(*L) == 0) 
            p = &(*L); // Va pointer vers le dernier endroit où se trouve un 0            
        L = &(**L).suivant;  
    }
    if (p == NULL)
        empile(x, L);
    else 
        empile(x, p); 
}


/*************************************************/
/*                                               */
/*           Tic                                 */
/*                                               */
/*************************************************/


void Tic(Liste *L)
{
    if (NOT estVide(*L)) {
        if (premier(*L) == 0) {
            while (premier(*L) == 0 && NOT estVide(*L))
                depile(L);
        } else {
            Tic(&(**L).suivant);
            empile(0, L);
        }
    }
}


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

// Switch de tests pour la procédure AjouteDevantDernierZero (selon ses 3 versions)
void AjouteDevantDernierZero(Liste L1, Liste L2, Liste L3, int i)
{
    printf("L1 : [5, 6, 7]\n");
    printf("L2 : [1, 2, 0, 3]\n");
    printf("L3 : [1, 0, 3, 4, 0, 6]\n");
    switch (i)  
    {
    case 1 : // Récursif (argument inout)
        printf("AjouteDevantDernierZero1(L1, 8, NULL) : \n");
        printf("AjouteDevantDernierZero1(L2, 9, NULL) : \n");
        printf("AjouteDevantDernierZero1(L3, 2, NULL) : \n");
        AjouteDevantDernierZero1(&L1, 8, NULL);            
        AjouteDevantDernierZero1(&L2, 9, NULL);            
        AjouteDevantDernierZero1(&L3, 2, NULL);
        break;
    case 2 : // Récursif terminal
        printf("AjouteDevantDernierZero2(L1, 8) : \n");
        printf("AjouteDevantDernierZero2(L2, 9) : \n");
        printf("AjouteDevantDernierZero2(L3, 2) : \n");
        AjouteDevantDernierZero2(&L1, 8);            
        AjouteDevantDernierZero2(&L2, 9);            
        AjouteDevantDernierZero2(&L3, 2);
        break;
    case 3 : // Itératif
        printf("AjouteDevantDernierZero3(L1, 8) : \n");
        printf("AjouteDevantDernierZero3(L2, 9) : \n");
        printf("AjouteDevantDernierZero3(L3, 2) : \n");
        AjouteDevantDernierZero3(&L1, 8);            
        AjouteDevantDernierZero3(&L2, 9);            
        AjouteDevantDernierZero3(&L3, 2);
        break;
    }
}

int main(int argc, char** argv)
{
    if (FALSE)
    {
    Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    VideListe(&l);
    }

    if (FALSE)
    {
    printf("Tests sur la fonction UnPlusDeuxEgalTrois: \n\n");
        
    Liste L1 = NULL;
    printf("Liste 1 : [], UnPlusDeuxEgalTrois : %d\n",
                          UnPlusDeuxEgalTrois(L1));

    Liste L2 = ajoute(0, NULL);
    printf("Liste 2 : [0], UnPlusDeuxEgalTrois : %d\n", 
                           UnPlusDeuxEgalTrois(L2));

    Liste L3 = ajoute(2, ajoute(-2, NULL));
    printf("Liste 3 : [2, -2], UnPlusDeuxEgalTrois : %d\n",
                               UnPlusDeuxEgalTrois(L3));

    Liste L4 = ajoute(0, ajoute(0, NULL));
    printf("Liste 4 : [0, 0], UnPlusDeuxEgalTrois : %d\n",
                              UnPlusDeuxEgalTrois(L4));        
                                  
    Liste L5 = ajoute(1, ajoute(0, NULL));
    printf("Liste 5 : [1, 0], UnPlusDeuxEgalTrois : %d\n",
                              UnPlusDeuxEgalTrois(L5));

    Liste L6 = ajoute(3, ajoute(5, ajoute(8, NULL)));
    printf("Liste 6 : [3, 5, 8], UnPlusDeuxEgalTrois : %d\n",
                                 UnPlusDeuxEgalTrois(L6));

    Liste L7 = ajoute(2, ajoute(3, ajoute(7, NULL)));
    printf("Liste 7 : [2, 3, 7], UnPlusDeuxEgalTrois : %d\n\n",
                                 UnPlusDeuxEgalTrois(L7));

    VideListe(&L1);
    VideListe(&L2);
    VideListe(&L3);
    VideListe(&L4);
    VideListe(&L5);
    VideListe(&L6);
    VideListe(&L7);
    }
    
    if (FALSE) // Croissante
    {
    printf("Tests sur la fonction Croissante: \n\n");

    Liste L1 = NULL;
    printf("Liste 1 : [], Croissante : %d\n", Croissante(L1));

    Liste L2 = ajoute(5, NULL);
    printf("Liste 2 : [5], Croissante : %d\n", Croissante(L2));

    Liste L3 = ajoute(2, ajoute(-2, NULL));
    printf("Liste 3 : [2, -2], Croissante : %d\n", Croissante(L3));

    Liste L4 = ajoute(0, ajoute(0, NULL));
    printf("Liste 4 : [0, 0], Croissante : %d\n", Croissante(L4));

    Liste L5 = ajoute(1, ajoute(2, ajoute(3, NULL)));
    printf("Liste 5 : [1, 2, 3], Croissante : %d\n", Croissante(L5));

    Liste L6 = ajoute(2, ajoute(3, ajoute(1, NULL)));
    printf("Liste 6 : [2, 3, 1], Croissante : %d\n", Croissante(L6));

    Liste L7 = ajoute(5, ajoute(6, ajoute(6, ajoute(7, NULL))));
    printf("Liste 7 : [5, 6, 6, 7], Croissante : %d\n\n", Croissante(L7));

    VideListe(&L1);
    VideListe(&L2);
    VideListe(&L3);
    VideListe(&L4);
    VideListe(&L5);
    VideListe(&L6);
    VideListe(&L7);
    }

    if (FALSE) // NombreMemePosition
    {

    printf("Tests sur la fonction NombreMemePosition: \n\n");

    Liste L1 = NULL;
    Liste L2 = NULL;
    printf("L1 : [], L2 : []\n"), 
    printf("NombreMemePosition1 : %d\n", NombreMemePosition1(L1, L2)); 
    printf("NombreMemePosition2 : %d\n", NombreMemePosition2(L1, L2)); 
    printf("NombreMemePosition3 : %d\n", NombreMemePosition3(L1, L2)); 
    printf("NombreMemePosition4 : %d\n\n", NombreMemePosition4(L1, L2)); 

    Liste L3 = NULL;
    Liste L4 = ajoute(3, NULL);
    printf("L3 : [], L4 : [3]\n"), 
    printf("NombreMemePosition1 : %d\n", NombreMemePosition1(L3, L4)); 
    printf("NombreMemePosition2 : %d\n", NombreMemePosition2(L3, L4)); 
    printf("NombreMemePosition3 : %d\n", NombreMemePosition3(L3, L4)); 
    printf("NombreMemePosition4 : %d\n\n", NombreMemePosition4(L3, L4)); 

    Liste L5 = ajoute(1, ajoute(2, ajoute(3, NULL)));
    Liste L6 = ajoute(1, ajoute(2, ajoute(3, NULL)));
    printf("L5 : [1, 2, 3], L6 : [1, 2, 3]\n");
    printf("NombreMemePosition1 : %d\n", NombreMemePosition1(L5, L6)); 
    printf("NombreMemePosition2 : %d\n", NombreMemePosition2(L5, L6)); 
    printf("NombreMemePosition3 : %d\n", NombreMemePosition3(L5, L6)); 
    printf("NombreMemePosition4 : %d\n\n", NombreMemePosition4(L5, L6)); 

    Liste L7 = ajoute(5, ajoute(6, NULL));
    Liste L8 = ajoute(6, ajoute(5, NULL));
    printf("L7 : [5, 6], L8 : [6, 5]\n");
    printf("NombreMemePosition1 : %d\n", NombreMemePosition1(L7, L8)); 
    printf("NombreMemePosition2 : %d\n", NombreMemePosition2(L7, L8)); 
    printf("NombreMemePosition3 : %d\n", NombreMemePosition3(L7, L8)); 
    printf("NombreMemePosition4 : %d\n\n", NombreMemePosition4(L7, L8)); 

    Liste L9 = ajoute(3, ajoute(6, ajoute(9, ajoute(0, ajoute(3, ajoute(4, ajoute(2, ajoute(9, ajoute(2, NULL)))))))));
    Liste L10 = ajoute(3, ajoute(9, ajoute(6, ajoute(0, ajoute(2, ajoute(2, ajoute(2, ajoute(2, ajoute(2, ajoute(5, NULL))))))))));
    printf("L9 : [3, 6, 9, 0, 3, 4, 2, 9, 2], \nL10 : [3, 9, 6, 0, 2, 2, 2, 2, 2, 2, 5]\n"); 
    printf("NombreMemePosition1 : %d\n", NombreMemePosition1(L9, L10)); 
    printf("NombreMemePosition2 : %d\n", NombreMemePosition2(L9, L10)); 
    printf("NombreMemePosition3 : %d\n", NombreMemePosition3(L9, L10)); 
    printf("NombreMemePosition4 : %d\n\n", NombreMemePosition4(L9, L10)); 

    VideListe(&L1);
    VideListe(&L2);
    VideListe(&L3);
    VideListe(&L4);
    VideListe(&L5);
    VideListe(&L6);
    VideListe(&L7);
    VideListe(&L8);
    VideListe(&L9);
    VideListe(&L10);
    }   

    if (TRUE) // FonctVireDernier
    {

    printf("Tests sur la fonction FonctVireDernier: \n\n");

    Liste L1; 
    Liste L2;
    Liste L3;
    Liste L4;

    initVide(&L1);
    initVide(&L2);
    initVide(&L3);
    initVide(&L4);

    empile(5, &L2);

    empile(3, &L3);
    empile(2, &L3);
    empile(1, &L3);

    empile(6, &L4);
    empile(5, &L4);
    empile(4, &L4);
    empile(3, &L4);
    empile(2, &L4);
    empile(1, &L4);
    
    printf("L1 : []\n");
    printf("FonctVireDernier1(L1) : "); affiche_iter(FonctVireDernier1(L1));
    printf("FonctVireDernier2(L1) : "); affiche_iter(FonctVireDernier2(L1));

    printf("\nL2 : [5]\n");
    printf("FonctVireDernier1(L2) : "); affiche_iter(FonctVireDernier1(L2));
    printf("FonctVireDernier2(L2) : "); affiche_iter(FonctVireDernier2(L2));
    
    printf("\nL3 : [1, 2, 3]\n");
    printf("FonctVireDernier1(L3) : "); affiche_iter(FonctVireDernier1(L3));
    printf("FonctVireDernier2(L3) : "); affiche_iter(FonctVireDernier2(L3));

    printf("\nL4 : [1, 2, 3, 4, 5, 6]\n");
    printf("FonctVireDernier1(L4) : "); affiche_iter(FonctVireDernier1(L4));
    printf("FonctVireDernier2(L4) : "); affiche_iter(FonctVireDernier2(L4));    
    

    VideListe(&L1);
    VideListe(&L2);
    VideListe(&L3);
    VideListe(&L4);
    }

    if (FALSE) // AjouteDevantPremierZero
    {

    printf("Tests sur la procécure AjouteDevantPremierZero: \n\n");

    Liste L1; 
    Liste L2;
    Liste L3;
    Liste L4;

    initVide(&L1);
    initVide(&L2);
    initVide(&L3);
    initVide(&L4);

    empile(5, &L2);

    empile(3, &L3);
    empile(0, &L3);
    empile(2, &L3);
    empile(1, &L3);

    empile(6, &L4);
    empile(0, &L4);
    empile(4, &L4);
    empile(3, &L4);
    empile(0, &L4);
    empile(1, &L4);


    printf("L1 : []");
    printf("\nAjouteDevantPremierZero(L1, 5) : "); AjouteDevantPremierZero(&L1, 5);
    affiche_iter(L1);

    printf("\nL2 : [5] : ");
    printf("\nAjouteDevantPremierZero(L2, 8) : "); AjouteDevantPremierZero(&L2, 8);
    affiche_iter(L2);
    
    printf("\nL3 : [1, 2, 0, 3] : ");
    printf("\nAjouteDevantPremierZero(L3, 9) : "); AjouteDevantPremierZero(&L3, 9);  
    affiche_iter(L3);

    printf("\nL4 : [1, 0, 3, 4, 0, 6] : ");
    printf("\nAjouteDevantPremierZero(L4, 2) : "); AjouteDevantPremierZero(&L4, 2);
    affiche_iter(L4);
    
    VideListe(&L1);
    VideListe(&L2);
    VideListe(&L3);
    VideListe(&L4);
    }

    if (FALSE) // AjouteDevantDernierZero
    {

    printf("Tests sur la procécure AjouteDevantDernierZero: \n\n");

    Liste L1; 
    Liste L2;
    Liste L3;

    initVide(&L1);
    initVide(&L2);
    initVide(&L3);

    empile(7, &L1);
    empile(6, &L1);
    empile(5, &L1);

    empile(3, &L2);
    empile(0, &L2);
    empile(2, &L2);
    empile(1, &L2);

    empile(6, &L3);
    empile(0, &L3);
    empile(4, &L3);
    empile(3, &L3);
    empile(0, &L3);
    empile(1, &L3);

    // Versions :
    // i = 1 : Récursif inout  
    // i = 2 : Récursif Terminal
    // i = 3 : Itératif
    AjouteDevantDernierZero(L1, L2, L3, 1);

    affiche_iter(L1);
    affiche_iter(L2);
    affiche_iter(L3);
        
    VideListe(&L1);
    VideListe(&L2);
    VideListe(&L3);
    }

    if (FALSE) // Tic
    {

    printf("Tests sur la procécure Tic: \n\n");

    Liste L1;

    initVide(&L1);

    empile(1, &L1);
    empile(2, &L1);
    empile(0, &L1);
    empile(0, &L1);
    empile(9, &L1);
    empile(8, &L1);
    empile(0, &L1);
    empile(0, &L1);
    empile(0, &L1);
    empile(2, &L1);
    empile(7, &L1);
    empile(3, &L1);

    printf("L1 : [3, 7, 2, 0, 0, 0, 8, 9, 0, 0, 2, 1]\n");
    printf("Tic(L1) : \n"); 
    Tic(&L1);

    affiche_iter(L1);

    VideListe(&L1);
    }

    return 0;
}





