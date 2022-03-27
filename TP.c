/* hayla kader khedma mliha ajbetni , hayla yaser lokan nakhadmo haka rah navanciu mlih.
1. manhtajouch les fonction:  acces_pos, acces_valeur, inserer, supp_pos

2. la fonction 'inserer'  normalment manhtajohach pcq ida konna rah nzdo athlethe f une liste 
ahsen tariqa hia nzidoh mn loul , mathemech lposition pcq aslan liste d'Athlethes mch ordonnes.
donc makallah nparcouri tous la list pour inserer une athlethe , ndirouh fi blaste la tete directe.

3. rani badelt le nom ta3 le pointeur t3 la tete fl procedure 'create' mn 'p' l 'tete' + badelt chwi f lfonction
mba3d nzid nfahmek fiha

4. mzal kayn problem fi random mba3d ntfahmo 3lih
*/

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

const int maxpays = 150;
const int maxepreuve = 200;

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

//modifite fiha chwy
ptr create()
{
    FILE* fichier;
    fichier = fopen("noms","r");// fichier 'noms' nhoto fih les noms li nehtajouhm
    ptr tete,tmp,nouv ;
    int n ;
    string x,y ;
    srand(time(NULL));
    n = rand() % 11 ;
    tete = NULL ;
    for (int i=0 ; i< n ; i++ )
    {
        nouv = malloc(sizeof(athlethe));
        nouv->suiv =NULL ;
        fgets(y,25,fichier);
        strcpy(nouv->nom, y);
        if ( tete==NULL)
        {
            tete = nouv ;
            tmp = nouv ;
            nouv = NULL;
        }
        else {
            tmp->suiv = nouv;
            tmp = nouv;
            nouv = NULL;
        }
    }
    fclose(fichier);
    return tete ;
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


//construire tableau tabpays
void creer_tabpays(char tabpays[maxpays][255]) //theb mba3d nfehmek fiha mlih
{
    char pay[255];
    FILE* fichier;
    fichier = fopen("pays","r");
    for(int i =1;i<maxpays;i++){
        fgets(pay,255,fichier);
        strcpy(tabpays[i],pay);
    }
    fclose(fichier);
}

//construire tableau tabepreuve
void creer_tabepreuve(char tabepreuve[maxepreuve][255]) 
{
    char epreuve[255];
    FILE* fichier;
    fichier = fopen("epreuve","r");
    for(int i =0;i<maxepreuve;i++){
        fgets(epreuve,255,fichier);
        strcpy(tabepreuve[i],epreuve);
    }
    fclose(fichier);
}
//construite le procedure creer tabjo

void creer_tabjo(ptr tabjo[maxepreuve][maxpays])
{
    for(int i=0;i< maxepreuve;i++){
        for(int j=0;j<maxpays;j++){
            tabjo[i][j] = create();
        }
    }
}

int main()
{
    int n ;
    string q;
    ptr  p ;
    p = create() ;
    afficher(p) ;
    printf("dsds %d ",longeur(p) ) ;
    //test tabepreuve et tabpays
    printf("\nles pays: \n");
    char tabpays[150][255];
    char tabpreuve[200][255];
    creer_tabpays(tabpays);
    creer_tabepreuve(tabpreuve);
    for(int i =0;i< 150;i++){
        printf("%s",tabpays[i]);
    }
    printf("\nles epreuves : ");
    for(int i =0;i<200;i++){
        printf("%s",tabpreuve[i]);
    }
    //test tabjo
    ptr tabjo[maxepreuve][maxpays];
    creer_tabjo(tabjo);
    printf("\n");
    afficher(tabjo[0][0]);
    afficher(tabjo[21][32]);
    afficher(tabjo[23][130]);
    return 0;
}
