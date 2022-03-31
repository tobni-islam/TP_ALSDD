#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef char  string[25]  ;

typedef struct athlethe
{
    string nom  ;
    struct athlethe *suiv ;
}athlethe ;

typedef athlethe  * ptr ; // nouveau type pour les pointeures ptr khirmn point

const unsigned MAX = 10;

const int maxpays = 150;
const int maxepreuve = 200;



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
    fichier = fopen("noms.txt","r");// fichier 'noms' nhoto fih les noms li nehtajouhm
    ptr tete,tmp,nouv ;
    int n ;
    string x,y ;
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

//hadi fonction tconverti ay string l lowercase
char *lower_case(char *str){
    for(int i= 0;str[i];i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

// hadi procedure tnahhilk les espaces men ay string    nhtajoha yaser
void supp_blanc(char* s) {
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

//construire tableau tabpays
void creer_tabpays(char tabpays[maxpays][255]) //theb mba3d nfehmek fiha mlih
{
    char pay[255];
    FILE* fichier;
    fichier = fopen("pays.txt","r");
    for(int i =0;i<maxpays;i++){
        fgets(pay,255,fichier);
        strcpy(pay,lower_case(pay));
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
        strcpy(epreuve,lower_case(epreuve));
        strcpy(tabepreuve[i],epreuve);
    }
    fclose(fichier);
}
//1 er procedure creer tabjo

void creer_tabjo(ptr tabjo[maxepreuve][maxpays])
{
    for(int i=0;i< maxepreuve;i++){
        for(int j=0;j<maxpays;j++){
            tabjo[i][j] = create();
        }
    }
}

// 2eme procedure (modifier)

void inserath(string nomath , int nump ,int nume , ptr tabjo[maxepreuve][maxpays] )
{
    ptr ath ; 
    ath = malloc(sizeof(athlethe));  //new maillon
    aff_nom(ath,nomath); 
    aff_adr(ath,tabjo[nume][nump]); //aff_adr  ath -->  tabjo(tete) 
    tabjo[nume][nump] = ath;  // la tete = new maillon.
}

int verif_pays (string pays , char tabpays[maxpays][255] ) // tgolk ida kayn had l pays wla non
{
    int trouv =0;
    char str[255];
    supp_blanc(pays);
    strcpy(pays,lower_case(pays));
    for (int i = 0 ; i< maxpays ; i++)
    {
        strcpy(str,tabpays[i]);
        supp_blanc(str);
        if (!(strcmp(str,pays)))
        {
            trouv = 1 ;
            return trouv;
        }
    }
    return trouv;
}

int verif_epreuve (string epreuve , char tabepreuve[maxepreuve][255]) // tgolk ida kayn l'epreuve li d5ltha wla non  wla non
{
    int trouv = 0 ;
    char str[255];
    supp_blanc(epreuve);
    strcpy(epreuve,lower_case(epreuve));
    for (int i = 0 ; i< maxepreuve; i++)
    {
        strcpy(str,tabepreuve[i]);
        supp_blanc(str);
        if (!(strcmp(tabepreuve[i],epreuve)))
        {
            trouv = 1 ;
            return trouv;
        }
    }
    return trouv ;
}



int indice_pays(string pays , char tabpays[maxpays][255] ) // tmdlha ism bled tmdlk numero te3o
{
        for (int i = 0; i < maxpays; i++)
        {
            if (!(strcmp(tabpays[i], pays)))
                return i;
        }
}

int indice_epreuve(string epreuve, char tabepreuve[maxepreuve][255]) // wla epreuve nfs lkhdma galna t9dro tzido parametre
{
        for (int i = 0; i < maxepreuve; i++)   // mlgitch kifah ndkhl tabpays psa mahoch parametre
        {
            if (!(strcmp(tabepreuve[i], epreuve)))
                return i;
        }
}


 // 3eme procedure

void listathpays(string pays , char tabpays[maxpays][255] , char tabepreuve [maxepreuve][255] , ptr tabjo[maxepreuve][maxpays])
{
    int trouv = 0 ;
    if (verif_pays(pays,tabpays))
    {
   int p =  indice_pays(pays,tabpays); // on stocke l 'indice te3 lpays f p
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
    ptr  p ;
    p = create() ;
    //test tabepreuve et tabpays
    srand(time(0));
    char tabpays[150][255];
    char tabepreuve[200][255];
    ptr tabjo[200][150];
    creer_tabpays(tabpays);
    creer_tabepreuve(tabepreuve);
    creer_tabjo(tabjo);
    
   return 0;
}
