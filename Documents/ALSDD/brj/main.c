#include<stdio.h>
#include<stdlib.h>
//islam chikour
typedef struct node
{
    int value ;
    struct node *next ;
}node;

node *create()
{
    node *p ;
    int x,n,y ;
    p = malloc(sizeof(node)) ;
    printf("entrez le nombre des elemnts : ");
    scanf("%d",&n);
    printf("entrez la valeur de la tete : ");
    scanf("%d",&x);
    p ->value = x ;
    p->next = NULL ;
    node *tmp;
    tmp = p;
    for (int i=1 ; i<n ; i++ )
    {
        node *nouv ;
        nouv = malloc(sizeof( node)) ;
        printf("entrez la valeur de l'element :  ") ;
        scanf("%d",&y);
        nouv->value = y;
        nouv->next=NULL;
        tmp->next=nouv ;
        tmp = nouv ;
    }
    return p ;
}

node *acces_val(node *p , int val)
{
    node* tmp ;
    tmp = p ;
    while ( tmp != NULL)
    {
        if (tmp->value == val ) return tmp ;
        tmp = tmp ->next ;
    }
    printf ("la valeur n'existe pas ");
    return NULL ;
}


node *acces_pos (node *p , int pos)
{
    node *tmp;
    tmp = p ;
   int  cpt = 0 ;
        while ( tmp != NULL) {
            cpt += 1;
            if ( cpt == pos ) return tmp ;
            tmp = tmp->next;
        }
}

void supp_pos ( node *tete , int n )
{
    node *prec ,*p ;
    prec = acces_pos(tete , n-1 );
     p = prec->next  ;
    prec->next = p-> next ;
    free(p);

}
void supp_val ( node  *tete , int n ) {
    node *prec, *p;
    p = tete;
    if (p->value == n) {
        tete = tete->next;
    } else {
        while ((p != NULL) && (p->value != n)) {
            prec = p;
            p = p->next;
        }
        if (p == NULL) {
            printf("la valeur n'existe pas \n");
        } else {
            prec->next = p->next;
        }
    }
    free(p);
}

void inserer(node *p,int pos , int n )
{
    node *tmp,*suiv ,*prec;
    tmp = malloc(sizeof (node));
    tmp ->value = n ;
    prec = acces_pos(p,pos-1) ;
    suiv = prec-> next ;
    tmp -> next = suiv ;
    prec->next = tmp ;
}

void afficher(node *p)
{
    node *tmp ;
    tmp = p ;
    printf("la valeur :   \t \t  @:  \t \t      suivant : \n");

    while ( tmp != NULL)
    {
        printf("  %d \t \t  %p \t    %p  \n",tmp->value ,tmp , tmp->next);
        tmp = tmp -> next ;
    }
}

int length_llc(node *p)
{
    int cpt = 0 ;
    node *tmp = p ;
    while ( tmp != NULL)
    {
        cpt +=1 ;
        tmp = tmp->next ;
    }
    return cpt ;
}

node *interclass(node *t1 , node *t2 )
{
    node *p1,*p2,*p3,*t3;
    p1 = t1 ;
    p2 = t2 ;
    if ( t1->value < t2->value )
    {
        t3 = p1 ;
        p3 = p1 ;
        p1 = p1->next ;
    }
    else
    {
        t3 = p2 ;
        p3 = p2;
        p2 = p2 ->next  ;
    }
        while ( (p1 !=NULL) && (p2 != NULL ))
        {
            while ( ( p1 != NULL) && (p1->value < p2->value ))
            {
            p3 = p1 ;
            p1 = p1->next;
            }
            p3 -> next = p2;
            if ( p1 != NULL ) {
                while ((p2 != NULL) && (p1->value >= p2->value)) {
                    p3 = p2;
                    p2 = p2->next;
                }
                p3->next = p1;
            }
        }
    return t3 ;
}




int main ()
{
    node *p ,*q , *t  ;
    int val,a;
    p=create();
    afficher(p);
    q =create() ;
    afficher(q);
    t = interclass(p,q);
    afficher(t);
    return 0 ;
}


