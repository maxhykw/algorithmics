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
/*          definition type BlocZ, ListeZ        */
/*                                               */
/*************************************************/


typedef struct BlocZ {
    int val;
    struct BlocZ* next;
    struct BlocZ* prev;
} BlocZ;

typedef struct ListeZ {
    BlocZ* acces;
} ListeZ;


/*************************************************/
/*                                               */
/*                Prédéclarations                */
/*                                               */
/*************************************************/


/* affichage simple d'une ListeZ L */
void afficheListeZ(ListeZ L);

/* Libère la mémoire d'une ListeZ L */
void videListeZ(ListeZ *L);

/* Ajoute un nouveau bloc (contenant x) juste avant le bloc à l'intérieur
   duquel acces pointe */
void ZAjouteAvant(int x, ListeZ *L);


/*************************************************/
/*                                               */
/*              afficheListeZ                    */
/*                                               */
/*************************************************/


void afficheListeZ(ListeZ L) {
    if (L.acces == NULL) {
        printf("Liste vide\n");
        return;
    }

    BlocZ* current = L.acces;

    do {
        printf("%d ", current->val);
        current = current->next;
    } while (current != L.acces);

    printf("\n");
}


/*************************************************/
/*                                               */
/*               videListeZ                      */
/*                                               */
/*************************************************/


void videListeZ(ListeZ *L) {
    if (L->acces == NULL) 
        return;

    BlocZ* current = L->acces;
    BlocZ* suivant;

    // On libère la mémoire allouée pour chaque élément 
    do {
        suivant = current->next;
        free(current);
        current = suivant;

    } while (current != L->acces);

    L->acces = NULL; // Pour indiquer que la liste est désormais vide 
}


/*************************************************/
/*                                               */
/*                 ZAjouteAvant                  */
/*                                               */
/*************************************************/


void ZAjouteAvant(int x, ListeZ *L) {
    BlocZ* newBloc = (BlocZ*)malloc(sizeof(BlocZ));
    newBloc->val = x;

    if (L->acces == NULL) {
        // Cas où la liste est vide : on rend le nouveau bloc circulaire
        newBloc->next = newBloc;
        newBloc->prev = newBloc;

        L->acces = newBloc;
    } else {
        // Sinon on insère le nouveau bloc juste avant le bloc pointé par acces
        BlocZ* blocAvant = L->acces->prev;

        blocAvant->next = newBloc;
        newBloc->prev = blocAvant;

        newBloc->next = L->acces;
        L->acces->prev = newBloc;
    }
    // On met à jour le pointeur acces pour pointer vers le nouveau bloc ajouté
    L->acces = newBloc;
}


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{
    ListeZ maListe;
    maListe.acces = NULL;

    ZAjouteAvant(42, &maListe);
    afficheListeZ(maListe);

    ZAjouteAvant(93, &maListe);
    afficheListeZ(maListe);

    ZAjouteAvant(17, &maListe);
    afficheListeZ(maListe);

    ZAjouteAvant(23, &maListe);
    afficheListeZ(maListe);

    videListeZ(&maListe);

    return 0;
}