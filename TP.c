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

void aff_nom (ptr p , string n  )
{
    strcpy(p->nom,n) ;
}

//modifite fiha chwy
ptr create()
{
    FILE* fichier;
    fichier = fopen("nom.txt","r");// fichier 'noms' nhoto fih les noms li nehtajouhm
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
    fichier = fopen("pays.txt","r");
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
    fichier = fopen("epreuve.txt","r");
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

// 2eme procedure

void inserath(string nomath , int nump ,int nume , ptr tabjo[maxepreuve][maxpays] )
{
    ptr ath ;
    ath = malloc(sizeof(athlethe));     // athlethe li hab ndirolo insertion
    aff_nom(ath,nomath);
    ath ->suiv = NULL ;
    ptr p = tabjo[nume][nump]->suiv;      // hada 2eme maillon habin nrbtoh bl athlethe jdid bah nchainiw bah mnperdiwch la liste
    ath->suiv = p ;                      // linkage m3a 2eme maillon
    (tabjo[nume][nump])->suiv = ath;    //linkage te3 head m3a ath jdid
    (tabjo[nume][nump]) = ath ;        // tete twli hiya ath jdid .
}

int verif_pays (string pays , char tabpays[maxpays][255] ) // tgolk ida kayn had l pays wla non
{
    int trouv = 0 ;
    for (int i = 0 ; i< maxpays ; i++)
    {
        if (!(strcmp(tabpays[i],pays)));
        {
            trouv = 1 ;
            break ;
        }
    }
    return trouv ;
}

int verif_epreuve (string epreuve , char tabepreuve[maxepreuve][255]) // tgolk ida kayn l'epreuve li d5ltha wla non  wla non
{
    int trouv = 0 ;
    for (int i = 0 ; i< maxepreuve; i++)
    {
        if (!(strcmp(tabepreuve[i],epreuve)));
        {
            trouv = 1 ;
            break ;
        }
    }
    return trouv ;
}



int indice_pays(string pays , char tabpays[maxpays] [250] ) // tmdlha ism bled tmdlk numero te3o
{
        for (int i = 0; i < maxpays; i++)
        {
            if (!(strcmp(tabpays[i], pays)))
                return i;
        }
}

int indice_epreuve(string epreuve, char tabepreuve[maxepreuve] [250]) // wla epreuve nfs lkhdma galna t9dro tzido parametre
{
        for (int i = 0; i < maxepreuve; i++)   // mlgitch kifah ndkhl tabpays psa mahoch parametre
        {
            if (!(strcmp(tabepreuve[i], epreuve)))
                return i;
        }
}


 // 3eme procedure

void listathpays(string pays , char tabpays[maxepreuve][255] , char tabepreuve [maxepreuve][255] , ptr tabjo[maxepreuve][maxpays])
{
    int trouv = 0 ;
    if (verif_pays(pays,tabpays[maxpays][255]))
    {
   int p =  indice_pays(pays,tabpays[maxepreuve]); // on stocke l 'indice te3 lpays f p
   for (int i=0 ; i<maxepreuve ; i ++)
   {
       if (tabjo[i][p] != NULL) {
           printf("%s", tabepreuve[i]); //afficher l'epreuve
           afficher(tabjo[i][p]);// afficher la liste
           trouv = 1 ; // m3naha lgina au moins epreuve wahda
       }
   }
   if ( trouv == 0 ) printf(" ce pays n'aucun concurrent ")  ; // kayn f tabpays bsah m3ndoch athlethe
   }
    else  printf("ce pays n'existe pas ") ; // l ism li dkhlto ghalt
}

int main()
{
    int n ;
    string q;
    ptr  p ;
    p = create() ;
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
    afficher(tabjo[1][2]);
    afficher(tabjo[2][13]);
    return 0;
}
