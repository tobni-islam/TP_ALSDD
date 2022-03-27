#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

typedef char  string[25]  ;

typedef struct athlethe
{
    string nom  ;
    struct athlethe *suiv ;
}athlethe ;

typedef athlethe  * ptr ; // nouveau type pour les pointeures ptr khirmn point 

#define null NULL  // hadi b3thali aymen mb3d nfhmk fiha 
const unsigned MAX = 10;
const int nbCountries = 195;

// reads n lines of a text file
//returns 0 if an error occurs
int dispTextStr(char *file,int n)
{
    FILE *f = fopen(file, "r");
    int nbAcc = 0;
    if (f == null)
        return 0;
    else
    {
        char buffer[MAX];
        for(int i =0 ; i<n;i++)
        {
            fscanf(f,"%s",buffer);
            printf("%s ",buffer);

        }
        fclose(f);
        return 1;
    }
}



void allouer (ptr p ) //mat5dmch biha mahich mliha
{
    p = malloc(sizeof(athlethe));
    p->suiv =NULL ;
}

ptr suivant(ptr g ) // hadi kifkif akhtik mnha fiha probleme hiya w allouer brk
{
    return ( g->suiv ) ;
}

void liberer(ptr p )
{
    free(p);
}

void aff_adr(ptr p , ptr q)
{
    p->suiv =  q ;
}

void aff_nom (ptr p , char n[50] )
{
    strcpy(p->nom,n) ;
}


ptr create()
{
    ptr p,tmp,nouv ;
    int n ;
    string x,y ;
    srand(time(0));
    n = rand() % 11 ;
    if (n==0)
    {
        return  0 ;
    }
    p = NULL ;
    for (int i=0 ; i< n ; i++ )
    {
        nouv = malloc(sizeof (athlethe));
        nouv->suiv= NULL ;
        scanf("%s", y);
        strcpy(nouv->nom, y);
        if ( p==NULL)
        {
            p = nouv ;
            tmp = nouv ;
        }
        else {
            tmp->suiv = nouv;
            tmp = nouv;
            nouv = NULL;
        }
    }
    return p ;
}

ptr acces_pos (ptr p , int pos)
{
    ptr tmp;
    tmp = p ;
    int  cpt = 0 ;
    while ( tmp != NULL) {
        cpt += 1 ;
        if ( cpt == pos ) return tmp ;
        tmp = tmp->suiv ;
    }
}


ptr acces_val(ptr p , string val)
{
    ptr tmp ;
    tmp = p ;
    while ( tmp != NULL)
    {
        if (tmp->nom == val ) return tmp ;
        tmp = tmp ->suiv ;
    }
    printf ("la valeur n'existe pas ");
    return NULL ;
}

void afficher(ptr p)
{
    ptr tmp ;
    tmp = p ;
    printf("les participant sont  : ");
    while ( tmp != NULL)
    {
        printf("-> %s ",tmp->nom );
        tmp = tmp -> suiv ;
    }
    printf("\n") ;
}

void inserer(ptr p , int pos , string n  )
{
    ptr tmp,next ,prec;
    tmp = malloc(sizeof (athlethe));
    strcpy(tmp->nom , n );
    prec = acces_pos(p,pos-1) ;
    next = prec-> suiv ;
    tmp -> suiv = next ;
    prec->suiv = tmp ;
}

void supp_pos (ptr tete , int n )
{
    ptr prec ,p ;
    prec = acces_pos(tete , n-1 );
    p = prec->suiv  ;
    prec->suiv = p-> suiv;
    free(p);
}

void supp_nom (ptr tete , string n )
{
    ptr  prec, p;
    p = tete;
    if (p->nom == n) {
        tete = tete->suiv;
    }
    else {
        while ((p != NULL) && (strcmp(p->nom ,n)))
        {
            prec = p;
            p = suivant(p);
        }
        if (p == NULL) {
            printf("la valeur n'existe pas \n");
        } else {
            prec->suiv = p->suiv ;
        }
    }
    liberer(p);
}

int longeur(ptr p)
{
    int cpt = 0 ;
    ptr tmp = p ;
    while ( tmp != NULL)
    {
        cpt +=1 ;
        tmp = tmp->suiv ;
    }
    return cpt ;
}

int main()
{
    int n ;
    string q;
    ptr  p ;
    p = create() ;
    afficher(p) ;
    printf("dsds %d ",longeur(p) ) ;
    return 0;
}
