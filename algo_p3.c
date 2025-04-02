#include <stdio.h>
#include <stdlib.h>

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
/*          definition type bloc_image           */
/*                                               */
/*************************************************/

typedef struct bloc_image
{   
    bool quatre ;
    struct bloc_image *hg, *hd, *bg, *bd ;
} bloc_image ;

typedef bloc_image *image ; 

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    image img;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

image Blanc()
{
    image img = (image)malloc(sizeof(bloc_image));
    img->quatre = FALSE;
    img->hg = img->hd = img->bg = img->bd = NULL;
    return img;
}

image Noir()
{
    return NULL;
}

image Compose(image i0, image i1, image i2, image i3)
{
    image img = (image)malloc(sizeof(bloc_image));
    img->quatre = TRUE;
    img->hg = i0;
    img->hd = i1;
    img->bg = i2;
    img->bd = i3;
    return img;
}

/*************************************************/
/*                                               */
/*             briques de base (2)               */
/*                                               */
/*************************************************/

void initVide(Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

image premier(Liste l)
{
    return l->img ; 
}

Liste ajoute(image x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->img = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(image x, Liste *L)
{
      *L = ajoute(x, *L) ; 
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
/*                Libérer mémoire                */
/*                                               */
/*************************************************/

void VideMemoire(image img) {
    if (img != NULL) {
        if (img->quatre) {
            VideMemoire(img->hg);
            VideMemoire(img->hd);
            VideMemoire(img->bg);
            VideMemoire(img->bd);
        }
        free(img);
    }
}
/*************************************************/
/*                                               */
/*                Affichage                      */
/*                                               */
/*************************************************/

void AffichageBis(image img)
{
    if (img == NULL)
        printf("X"); // Noir
    else if (NOT img->quatre)
        printf("o"); // Blanc
    else {
        AffichageBis(img->hg);
        AffichageBis(img->hd);
        AffichageBis(img->bg);
        AffichageBis(img->bd);
        printf("*");
    }
}

void Affichage(image img)
{
    AffichageBis(img);
    printf("\n");
}


void AffichagePBis(image img, int profondeur)
{
    if (img == NULL)
        printf("X%d", profondeur); // Noir
    else if (NOT img->quatre)
        printf("o%d", profondeur); // Blanc
    else {
        AffichagePBis(img->hg, profondeur + 1);
        AffichagePBis(img->hd, profondeur + 1);
        AffichagePBis(img->bg, profondeur + 1);
        AffichagePBis(img->bd, profondeur + 1);
        printf("*%d", profondeur);
    }
}

void AffichageProfondeur(image img)
{
    AffichagePBis(img, 0);
    printf("\n");
}

/*************************************************/
/*                                               */
/*                Lecture                        */
/*                                               */
/*************************************************/


image Lecture()
{
    Liste P;
    initVide(&P);

    char ch = getchar(); 
    while (ch != '!') {
        
        if (ch == 'o')
            empile(Blanc(), &P);
        else if (ch == 'X')
            empile(Noir(), &P);
        else if (ch == '*')
        {
            // On sort de la pile, respectivement 
            image w = premier(P); depile(&P);
            image x = premier(P); depile(&P);             
            image y = premier(P); depile(&P);
            image z = premier(P); depile(&P); 

            empile((Compose(z, y, x, w)), &P);
        }
        ch = getchar();
    } 
    

    return premier(P); // P est un singleton 
}


/*************************************************/
/*                                               */
/*              Identificateurs                  */
/*                                               */
/*************************************************/

bool EstNoire(image img)
{
    if (img == NULL)
        return TRUE;
    else if (NOT img->quatre)
        return FALSE;
    else 
        return EstNoire(img->hg) &&
               EstNoire(img->hd) &&
               EstNoire(img->bg) &&
               EstNoire(img->bd);
}

bool EstBlanche(image img)
{
    if (img == NULL)
        return FALSE;
    else if (NOT img->quatre)
        return TRUE;
    else
        return EstBlanche(img->hg) &&
               EstBlanche(img->hd) &&
               EstBlanche(img->bg) &&
               EstBlanche(img->bd);
}

/*************************************************/
/*                                               */
/*              Aire                             */
/*                                               */
/*************************************************/

float AireBis(image img, float a)
{
    if (EstNoire(img))
        return a;
    else if (EstBlanche(img))
        return 0;
    else
        return AireBis(img->hg, a * 0.25) +
               AireBis(img->hd, a * 0.25) +
               AireBis(img->bg, a * 0.25) +
               AireBis(img->bd, a * 0.25);
}

float Aire(image img)
{
    return AireBis(img, 1.0);
}

/*************************************************/
/*                                               */
/*             Triangle bas-droit                */
/*                                               */
/*************************************************/

image TriangleBD(int p)
{
    if (p == 0)
        return Blanc();
    else
        return Compose(Blanc(), TriangleBD(p-1), TriangleBD(p-1), Noir());
}

/*************************************************/
/*                                               */
/*             Arrondit                          */
/*                                               */
/*************************************************/

void Arrondit(image *img, int p)
{
    if (p == 0) {
        if (Aire(*img) >= 0.5) { 
            // Noir
            image tmp = *img;
            *img = NULL; 
            VideMemoire(tmp);
        } else {
            // Blanc
            image tmp = *img;
            (*img) = Blanc();
            VideMemoire(tmp);
            }
    }
    else if ((*img != NULL) && (*img)->quatre) {
        Arrondit(&(*img)->hg, p-1);
        Arrondit(&(*img)->hd, p-1);
        Arrondit(&(*img)->bg, p-1);
        Arrondit(&(*img)->bd, p-1);

    } 
}

/*************************************************/
/*                                               */
/*              MemeDessin                       */
/*                                               */
/*************************************************/

/*
bool MemeDessin(image img1, image img2)
{
    if ((EstBlanche(img1) && EstBlanche(img2))
     || (EstNoire(img1)   && EstNoire(img2) ))
        return TRUE;

    else if ((EstNoire(img1) && EstBlanche(img2))
          || (EstNoire(img2) && EstBlanche(img1)))
        return FALSE;
    // Si on peut creuser dans img1 et img2 
    else if (((img1 != NULL && img1->quatre)
            && img2 != NULL && img2->quatre))
        return MemeDessin(img1->hg, img2->hg)
            && MemeDessin(img1->hd, img2->hd)
            && MemeDessin(img1->bg, img2->bg)
            && MemeDessin(img1->bd, img2->bd);
    // Si on peut ne peut continuer à creuser que dans img2..
    else if (img1 == NULL && (img2 != NULL && img2->quatre))
        return MemeDessin(img1, img2->hg)
            && MemeDessin(img1, img2->hd)
            && MemeDessin(img1, img2->bg)
            && MemeDessin(img1, img2->bd);
    // .. ou si on ne peut continuer à creuser que dans img1
    else 
        return MemeDessin(img1->hg, img2)
            && MemeDessin(img1->hd, img2)
            && MemeDessin(img1->bg, img2)
            && MemeDessin(img1->bd, img2);
}
*/

bool MemeDessin(image img1, image img2)
{
    if ((EstBlanche(img1) && EstBlanche(img2)) 
      || EstNoire(img1)   && EstNoire(img2))
        return TRUE;

    else if (EstBlanche(img1) || EstBlanche(img2)
          || EstNoire(img1)   || EstNoire(img2))
        return FALSE;

    return MemeDessin(img1->hg, img2->hg) &&
           MemeDessin(img1->hd, img2->hd) &&
           MemeDessin(img1->bg, img2->bg) &&
           MemeDessin(img1->bd, img2->bd);
}



/*************************************************/
/*                                               */
/*             InterUnion                        */
/*                                               */
/*************************************************/

void InterUnion(image *img1, image *img2)
{
    // Images racines différentes
    if ((*img1 == NULL && (*img2 != NULL && !(*img2)->quatre))
     || (*img2 == NULL && (*img1 != NULL && !(*img1)->quatre)))
    {
        (*img1) = Blanc();
        (*img2) = Noir();
    
    } // Deux images divisibles, on creuse jusque la racine
    else if ((*img1 != NULL && (*img1)->quatre) 
          && (*img2 != NULL && (*img2)->quatre))
    {
        InterUnion(&(*img1)->hg, &(*img2)->hg);
        InterUnion(&(*img1)->hd, &(*img2)->hd);
        InterUnion(&(*img1)->bg, &(*img2)->bg);
        InterUnion(&(*img1)->bd, &(*img2)->bd);
    
    } // Si img1 est Noire (et img2 encore divisible) 
    else if (*img1 == NULL) 
    {
        if (EstBlanche(*img2))
        {
            (*img1) = Blanc();
            (*img2) = Noir();
        } else {
            (*img1) = (*img2);
            // l'union donne quand même une image noire 
            (*img2) = Noir();
        }
    } // img2 blanche
    else if (*img2 != NULL AND !(*img2)->quatre) 
    {
        if ((*img1)->quatre)
        {
            (*img2) = (*img1);
            (*img1) = Blanc();
        }
    }
}

/*************************************************/
/*                                               */
/*              CompteDamiers                    */
/*                                               */
/*************************************************/

void CompteDAux(image img, int *acc)
{
    if (img == NULL || NOT img->quatre)
        return;

    else if (EstBlanche(img->hg) && EstBlanche(img->bd)
          && EstNoire(img->hd)   && EstNoire(img->bg) )
    {
        (*acc)++; 
        CompteDAux(img->hg, acc);
        CompteDAux(img->hg, acc);
        CompteDAux(img->hg, acc);
        CompteDAux(img->hg, acc);
    }
    else 
    {
        CompteDAux(img->hg, acc);
        CompteDAux(img->hg, acc);
        CompteDAux(img->hg, acc);
        CompteDAux(img->hg, acc); 
    }
}

int CompteDamiers(image img)
{
    if (img == NULL || NOT img->quatre)
        return 0;

    int res = 0;
    CompteDAux(img, &res);
    return res;
}

/*************************************************/
/*                                               */
/*              Main                             */
/*                                               */
/*************************************************/

int main(int argc, char** argv)
{
    if (FALSE) // Tests d'affichage
    {
    image i1 = Noir();
    image i2 = Blanc();
    image i3 = Compose(i1, i1, i2, i1);
    image i4 = Compose(i3, i3, Blanc(), i3);

    Affichage(i1); 
    Affichage(i2); 
    Affichage(i3); 
    Affichage(i4);

    AffichageProfondeur(i1);
    AffichageProfondeur(i2); 
    AffichageProfondeur(i3); 
    AffichageProfondeur(i4); 

    VideMemoire(i1);
    VideMemoire(i2);
    VideMemoire(i3);
    VideMemoire(i4);
    }

    if (FALSE) // Test Lecture()
    {
    Affichage(Lecture());
    }

    if (FALSE) // Tests EstNoire() ; EstBlanche()
    {
    image i1 = Noir();
    image i2 = Blanc();
    image i3 = Compose(i1, i1, i2, i1);
    image i4 = Compose(i3, i3, Blanc(), i3);
    
    image comp_nr = Compose(i1, i1, i1, i1);
    image comp_bl = Compose(i2, i2, i2, i2);
    image i5 = Compose(comp_nr, comp_nr, comp_nr, comp_nr);
    image i6 = Compose(comp_bl, comp_bl, comp_bl, comp_bl);

    printf("Tests EstNoire():\n\n");
    Affichage(i1); printf("EstNoire() = %d\n", EstNoire(i1));
    Affichage(i2); printf("EstNoire() = %d\n", EstNoire(i2));
    Affichage(i3); printf("EstNoire() = %d\n", EstNoire(i3));
    Affichage(i4); printf("EstNoire() = %d\n", EstNoire(i4));
    Affichage(i5); printf("EstNoire() = %d\n", EstNoire(i5));
    Affichage(i6); printf("EstNoire() = %d\n", EstNoire(i6));

    printf("\nTests EstBlanche():\n\n");
    Affichage(i1); printf("EstBlanche() = %d\n", EstBlanche(i1));
    Affichage(i2); printf("EstBlanche() = %d\n", EstBlanche(i2));
    Affichage(i3); printf("EstBlanche() = %d\n", EstBlanche(i3));
    Affichage(i4); printf("EstBlanche() = %d\n", EstBlanche(i4));
    Affichage(i5); printf("EstBlanche() = %d\n", EstBlanche(i5));
    Affichage(i6); printf("EstBlanche() = %d\n", EstBlanche(i6));

    VideMemoire(i1);
    VideMemoire(i2);
    VideMemoire(i3);
    VideMemoire(i4);
    VideMemoire(comp_bl);
    VideMemoire(comp_nr);
    VideMemoire(i5);
    VideMemoire(i6);
    }

    if (FALSE) // Tests fonction Aire()
    {
    image i1 = Lecture();
    printf("%f\n", Aire(i1)); // Aire(XoXoo*XXXXo**) = 0.75
    }

    if (FALSE) // Tests TriangleBD()
    {
    printf("TriangleBD(0) = "); Affichage(TriangleBD(0));
    printf("TriangleBD(1) = "); Affichage(TriangleBD(1));
    printf("TriangleBD(2) = "); Affichage(TriangleBD(2));
    printf("TriangleBD(3) = "); Affichage(TriangleBD(3));
    }

    if (FALSE) // Tests Arrondit()
    {
    image i1 = Lecture();
    
    printf("i1 : "); Affichage(i1);
    Arrondit(&i1, 2);
    printf("Arrondit(i1, 2) = "); Affichage(i1);
    
    VideMemoire(i1);
    }

    if (FALSE) // Tests MemeDessin()
    {
    image i1 = Lecture();
    image i2 = Lecture();

    printf("i1 : "); Affichage(i1);
    printf("i2 : "); Affichage(i2);
    printf("MemeDessin(i1, i2) = %d\n", MemeDessin(i1, i2));

    }

    if (FALSE) // Tests InterUnion()
    {
    image i1 = Lecture();
    image i2 = Lecture();

    printf("i1 : "); Affichage(i1);
    printf("i2 : "); Affichage(i2);
    printf("InterUnion(i1, i2) :\n");

    InterUnion(&i1, &i2);
    
    printf("i1 : "); Affichage(i1);
    printf("i2 : "); Affichage(i2);
   
    }

    if (TRUE) // Tests CompteDamiers()
    {
    image i1 = Compose(Blanc(), Noir(), Noir(), Blanc());
    printf("%d \n", CompteDamiers(i1));
    }

    return 0;
}