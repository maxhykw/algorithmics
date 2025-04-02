

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

typedef enum { false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0) 
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n)
{ long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/

float epsilon = 1e-10;  // Précision décimale


float Efloat () {
    float e = 1.0;
    float current = 1.0; // car 1/0! = 1
    int n = 1;
    while (true) 
    {
        current /= n; // revient à multiplier le dénomonateur par n (incrémenté) à chaque itération 
        e += current; 
        n++;

        if (current < epsilon) break;
    }
    return e;
} 

/*************************************************/

double Edouble () {   
    double e = 1.0;
    double current = 1.0; 
    int n = 1;
    while (true) 
    {
        current /= n;
        e += current; 
        n++;

        if (current < epsilon) break;
    }
    return e;
} 

/*************************************************/

long double Elongdouble () { 
    long double e = 1.0;
    long double current = 1.0; 
    int n = 1;
    while (true) 
    {
        current /= n;
        e += current; 
        n++;

        if (current < epsilon) break;
    }
    return e;
} 

/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/


/***
 * Constat : 

 * Alors que la suite tend vers 0 mathématiquement parlant, on peut observer que pour 
 * la version de type float, les résultats commencent à croître dès le 10ème terme de 
 * la suite -de manière exponentielle quelques termes après-, ce qui est intéressant.
 * Cela doit être dû au fait que les nombres en questions soient trop petits. On peut
 * faire le même constat pour la version de type double et long double, pour lesquels 
 * les valeurs commencent à croître à partir du 15ème terme.

***/


void afficheYfloat (int n) {
  float y = Efloat() - 1;
  for (int cpt = 1; cpt < n; cpt++) {
      printf("Float ; y%d = %.15f\n", cpt, y);
      y = cpt*y - 1;
  }
}

/*************************************************/

void afficheYdouble (int n) {
  double y = Edouble() - 1;
  for (int cpt = 1; cpt < n; cpt++) {
      printf("Double ; y%d = %.15f\n", cpt, y);
      y = cpt*y - 1;
  }
}

/*************************************************/

void afficheYlongdouble (int n) {
  long double y = Elongdouble() - 1;
  for (int cpt = 1; cpt < n; cpt++) {
      printf("Long double ; y%d = %.15Lf\n", cpt, y);
      y = cpt*y - 1;
  }
}




/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/

/***
 * Constats : 

 * a/ La suite (1 + 1/N)^N semble tendre vers la valeur de e. 


 * b/ Version 1, 3, 4 : semble ne pas pouvoir gérer les nombres au-delà de N = 10^5 
 *                      (erreur de segmentation) ; 
 *    
 *    Version 2, 5 : semble ne pas pouvoir gérer les nombres au-delà de N = 10^9 ; 
 * 
 *    Version 6 à 10 : gère avec efficacité toues les N. Cependant, donne environ 
 *                     2,716 comme valeur à partir de N = 10^13, puis 3,03 
 *                     pour N = 10^15
 * 
 * 
 * c/ Ainsi pour ces dernières, le compilateur semble bien effectuer l'optimisation 
 *    du récursif terminal, notamment au vu de la vitesse des calculs.
 * 
***/

double PW1 (double x, long n) {
    if (n == 0) 
        return 1;
    return x * PW1(x, n-1);    
}

double power1 (double x, long n) {
    if (n < 0) {
        x = 1/x;
        n = -n;
    }
    return PW1(x, n);
}

/*************************************************/

double power2a (double x, long n) { 
    if (n < 0) {
      x = 1/x;
      n = -n;
    }
    double pow = 1.0;
    for (int i = 1 ; i <= n ; i++) {
        pow *= x;
    }
    return pow;
}

/*************************************************/

double power2b (double x, long n) { 
    double pow = 1.0;
    while (n > 0) {
      pow *= x;
      n--;
    }
    return pow;
}

/*************************************************/

void pow3(double x, long n, double *r) {
  if (n == 0) 
      return; 
  *r *= x;
  pow3(x, n-1, r);
}

double power3 (double x, long n) { 
    double r = 1.0;
    pow3(x, n, &r);
    return r;
}

/*************************************************/

double pow4(double x, long n, double r) {
  if (n == 0)
      return r;
  return pow4(x, n-1, r*x);
}

double power4 (double x, long n) {
  return pow4(x, n, 1);
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m

double power5 (double x, long n)
{
    if (n == 0)
         return 1 ;
    else if (n % 2 == 0)
              return (power5(x, n/2) * power5(x, n/2)) ;
         else return (power5(x, n/2) * power5(x, n/2) * x) ;   
}

/*************************************************/

double power6 (double x, long n) {
    if (n == 0)
        return 1;
    else {
        double y = power6(x, n/2);
        if (n % 2 == 0) 
            return y * y;
        else 
            return y * y * x;
    }
}

/*************************************************/

double power7 (double x, long n) {
    if (n == 0) 
        return 1;
    else {
      if (n % 2 == 0) 
          return power7(x*x, n/2);
      else 
          return power7(x*x, n/2) * x;
    }
}

/*************************************************/

double pow8(double x, long n, double r) {
  if (n == 0) 
      return r;
  else {
    if (n % 2 == 0) 
        return pow8(x*x, n/2, r);
    else 
        return pow8(x*x, n/2, r*x);
  }
}

double power8 (double x, long n) {
  return pow8(x, n, 1);
}

/*************************************************/

void pow9(double x, long n, double *r) {
    if (n == 0)
        return ;
    else {
      if (n % 2) 
          *r *= x;
      pow9(x*x, n/2, r);
    }
}

double power9 (double x, long n) {
    double r = 1.0;
    pow9(x, n, &r);
    return r;
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat

double power10 (double x, long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

double power (double x, long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ; break ;
   case 2 : return power2a(x,n) ; break ;  // 2 pour 2a
   case 0 : return power2b(x,n) ; break ; // 0 pour 2b
   case 3 : return power3(x,n) ; break ;
   case 4 : return power4(x,n) ; break ;
   case 5 : return power5(x,n) ; break ;
   case 6 : return power6(x,n) ; break ;
   case 7 : return power7(x,n) ; break ;
   case 8 : return power8(x,n) ; break ;
   case 9 : return power9(x,n) ; break ;
  case 10 : return power10(x,n) ; break ;
     default : return 0 ; 
   }
}

   // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/

    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

long double power11 (long double x, long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

float power12 (float x, long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}


/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/


/***
 * Constats : 

 * Lorsque l'on tente de calculer A(6,0), la fonction tourne sans donner de résultat, 
 * car elle est en réalité une fonction infinie. En effet, A(6,0) est égal à A(5,A(6,0 - 1))
 * et ainsi de suite, sans jamais atteindre une valeur de base.
 * 
 * Les différentes versions ont des comportements similaires, mais ont toutefois des
 * différences de performance et de consommation mémoire, en fonction de leur implémentation.
 * En effet, la version 1 utilise une récursion profonde et peut entraîner une dépassement
 * de la pile, tandis que la deuxième utilise une récursion plus "superficielle" de la pile
 * et une itération pour éviter ce problème. La version 3 utilise une itération en m et une 
 * récursion en n, tandis que la version 4 utilise une itération pure en m et n. La 5ème
 * version est enfin une optimisation de la quatrième qui utilise moins de mémoire en évitant de 
 * stocker des valeurs intermédiaires.
 * 
***/


int A1(int m, int n) { 
    if (m == 0) 
        return n + 1;
    else { 
        if (n == 0)
            A1(m-1, 1);
        else 
            A1(m-1, A1(m, n-1));
    }   
}

int Ackermann1 (int m) {
  return A1(m, 0);
}

/*************************************************/

int A2(int m, int n) {
    if (m == 0)
        return n + 1;
    else {
        int r = 1;
        for (int i = 1; i <= n + 1; i++)
            r = A2(m-1, r);
        return r;
    }
}

int Ackermann2 (int m) {
    return A2(m, 0);
}

/*************************************************/

int AckermannT (int m) {
    int n = 1;
    while (m > 1) {
        if (n == 0) {
            n = 1;
        } else {
            n = A1(m - 1, n);
        }
        m--;
    }
    return n;
}

int A3(int m, int n) {
    while (m > 0) {
        if (n == 0) {
            m--;
            n = 1;
        } else {
            m--;
            n = A3(m, n - 1);
        }
    } 
    return n + 1;
}

int Ackermann3(int m) {
    return A3(m, 0);
}

/*************************************************/

int Ackermann4 (int m) {
    int pile[65550];   // Pile pour gérer les appels
    int p = -1;       // Pointeur (pour la pile)
    pile[++p] = m;    // On empile m
    int n = 1;

    while (p >= 0) {
        m = pile[p--]; // On dépile m, ajuste le pointeur 
        if (m == 0) {
            n++;       // Cas de terminaison
        } else {
            pile[++p] = m - 1;  // On empile m-1
            if (n == 0) {
                n = 1;
            } else { 
                pile[++p] = m;  // On empile m
                n--;
            }
        }
    }
    return n;
}

/*************************************************/

int Ackermann5 (int m) {
    int n = 1;
    while (m > 0) {
        if (n == 0) 
            n = 1;
        else {
            m--;
            n = m;
        }
    }
    return n + 1;
}

/*************************************************/
  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : return Ackermann1 (m) ; // break ;
   case 2 : return Ackermann2 (m) ; // break ;
   case 3 : return Ackermann3 (m) ; // break ;
   case 4 : return Ackermann4 (m) ; // break ;
   case 5 : return Ackermann5 (m) ; // break ;
   default : return 0 ; 
   }
}



/*************************************************/
/*                                               */
/*            Suite X                            */
/*                                               */
/*************************************************/



/******* Définition du logartihme (entier) ******/


int log_aux(int n, int *cpt) {
    if (n > 1) {
        (*cpt)++;
        log_aux(n / 2, cpt);
    }
}

int log_entier(int n) {
    int cpt = 0;
    log_aux(n, &cpt);
    return cpt;
}


/*************************************************/


int X1(int n) {
    int x = 2;
    for (int i = 1; i <= n; i++) {
        x = x + (log_entier(x) / log_entier(2));
    }
    return x;
}


/*************************************************/


int X2(int n) {
    if (n == 0) 
        return 2;
    else {
        int y = X2(n - 1);
        return y + log_entier(y) / log_entier(2);
    }
}


/*************************************************/


int X3_aux(int n, int x) {
    if (n == 0)
        return x;
    return X3_aux(n-1, x + (log_entier(x) / log_entier(2)));
}

int X3(int n) {
    return X3_aux(n, 2);
}


/*************************************************/


void X4_aux(int n, int x, int *res) {
    if (n == 0)
        return;
    *res = x + (log_entier(x) / log_entier(2));
    X4_aux(n - 1, *res, res);
}

int X4(int n) {
    int res = 2; 
    X4_aux(n, 2, &res);
    return res;
}


/*************************************************/


int suite_X (int n, int i) 
{ switch (i)  
   {
   case 1 : return X1(n) ;
   case 2 : return X2(n) ;
   case 3 : return X3(n) ;
   case 4 : return X4(n) ;
   default : return 0 ; 
   }
}


/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{

       double x ;
       long double y ;
       float z ;
       
       int cptx ;
  
       long nx ;
       
       int i,j ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (false) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (false) {     
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (false) {

     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (false) {  
       
        printf(" e1 = %.20f \n", Efloat()) ;
        printf(" e3 = %.30lf \n", Edouble()) ; 
        printf(" e3 = %.60Lf \n", Elongdouble()) ; 
        
}

if (false) {  
            afficheYfloat(30) ;
            afficheYdouble(30) ;
            afficheYlongdouble(30) ;
}
        
/******************    power     *******************************/

if (false) {  

        //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
        
        for(i=0 ; i<=10 ; i++)
        printf("Power %d dit que power(2,10) vaut %.0lf \n", i, power(2,10,i) ) ;
        
        printf("\n") ;
      
}

        
if (false) {  

        i=10 ;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++)
        {
        printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;

}
     
if (false) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;



}

/******************    Ackermann    *******************************/
                
if (false) { 
 
        for(i=1 ; i<=5 ; i++)  // numéro de version
        
        for(j=0 ; j<=5 ; j++)  // test de A(j,0) pour j de 0 à 5
        
        printf("Ack%d(%d) = %d \n", i, j, Ackermann(j,i)) ;
}


/******************    Suite X    ********************************/

if (false) {

    for (i = 1; i <= 4; i++)
    {
    printf("X%d(100) = %d \n", i, suite_X(100, i));
    }

}

/***********************************************************************/

    return 0;
}






