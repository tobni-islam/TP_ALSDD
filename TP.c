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

const int maxpays = 3;
const int maxepreuve = 3;



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
    fichier = fopen("noms","r");// fichier 'noms' nhoto fih les noms li nehtajouhm
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
    printf("les athlethes sont : \n");
    while ( tmp != NULL)
    {
        printf("   --> %s ",tmp->nom );
        tmp = tmp -> suiv ;
    }
    printf("\n") ;
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
    fichier = fopen("pays","r");
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
    fichier = fopen("epreuve","r");
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


//hadi fonction tverifier ida nom ath yexister f liste (True) w la non (False)
int verif_ath(string nomath,int nump, int nume, ptr tabjo[maxepreuve][maxpays]){
    int b = 0;
    ptr tmp = tabjo[nume][nump];
    while (tmp != NULL)
    {
        if(!strcmp(((*tmp).nom),nomath)){
            b = 1;
            return b;
        }
        aff_adr(tmp,tmp->suiv);
    }
    return b;

}
// 2eme procedure (modifier)

void inserath(string nomath , int nump ,int nume , ptr tabjo[maxepreuve][maxpays] )
{
    ptr tmp = tabjo[nume][nump] ;
    if((!verif_ath(nomath,nump,nume,tabjo)) && (longeur(tabjo[nume][nump]) < 10)) //Si nom ath n'exite pas et la longeur t3 liste < 10 donc inserer ath
    {
        ptr ath = malloc(sizeof(athlethe)); //new maillon
        aff_nom(ath,nomath); 
        aff_adr(ath,tabjo[nume][nump]);// aff_adr m3a la tete de liste
        tabjo[nume][nump] = ath;  // la nouveau tete est le nouveau maillon.
    }else if (longeur(tabjo[nume][nump]) == 10)
    {
        printf("Il y a déjà 10 athlètes inscrits, vous ne pouvez pas inserer un autre athlète!\n");
    }else{
        printf("il y a deja un athlethe inscrit avec ce nom.\n");
    }
}

int verif_pays (string pays , char tabpays[maxpays][255],int nbpays) // tgolk ida kayn had l pays wla non
{
    int trouv =0;
    char str[255];
    supp_blanc(pays);
    strcpy(pays,lower_case(pays));
    for (int i = 0 ; i< nbpays; i++)
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

int verif_epreuve (string epreuve , char tabepreuve[maxepreuve][255],int nbepreuve) // tgolk ida kayn l'epreuve li d5ltha wla non  wla non
{
    int trouv = 0 ;
    char str[255];
    supp_blanc(epreuve);
    strcpy(epreuve,lower_case(epreuve));
    for (int i = 0 ; i< nbepreuve; i++)
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



int indice_pays(string pays ,char tabpays[maxpays][255],int nbpays) // tmdlha ism bled tmdlk numero te3o
{
        for (int i = 0; i < nbpays; i++)
        {
            if (!(strcmp(tabpays[i], pays)))
                return i;
        }
        return (maxpays +1);
}

int indice_epreuve(string epreuve, char tabepreuve[maxepreuve][255],int nbepreuve) // wla epreuve nfs lkhdma galna t9dro tzido parametre
{
        for (int i = 0; i < nbepreuve; i++)   // mlgitch kifah ndkhl tabpays psa mahoch parametre
        {
            if (!(strcmp(tabepreuve[i], epreuve)))
                return i;
        }
        return(maxepreuve +1);
}


 // 3eme procedure

void listathpays(string pays , char tabpays[maxpays][255] ,int nbpays, char tabepreuve [maxepreuve][255] ,int nbepreuve, ptr tabjo[maxepreuve][maxpays])
{
    int trouv = 0 ;
    if (verif_pays(pays,tabpays,nbpays))
    {
   int p =  indice_pays(pays,tabpays,nbpays); // on stocke l 'indice te3 lpays f p
   for (int i=0 ; i<nbepreuve ; i ++)
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

// 4eme procedure
int sansath(int ne , ptr tabjo[maxepreuve][maxpays],int nbpays )
{
    int np ;
    int trouv = 1;
    for (np = 0 ; np <nbpays; np ++ )
    {
        if (tabjo[ne][np] != NULL ){
            trouv = 0;
            return trouv;
        }
    }
    return trouv;
}


//5eme procedure
void listjo(ptr tabjo[maxepreuve][maxpays],char tabpays[maxpays][255],int nbpays,char tabepreuve[maxepreuve][255],int nbepreuve){
    for(int i= 0;i<nbepreuve;i++){
        if(!sansath(i,tabjo,nbpays)){
            printf("%s",tabepreuve[i]);
            printf("######################################################\n");
            printf("\n");
            for(int j=0;j<nbpays;j++){
                printf("%s",tabpays[j]);
                printf("--------------------------\n");
                if(longeur(tabjo[i][j]) == 0){
                    printf("Ce pay n'a aucun athlethe en l'epreuve %s.\n",tabepreuve[j]);
                }else{
                    afficher(tabjo[i][j]);
                }
                printf("------------------------------------\n");
            }
        }
    }
}

//6eme procedure li tsuprimi
void suppays (string pays , ptr tabjo[maxepreuve][maxpays] ,char tabpays[maxpays][255] ,int *nbpays,int *nbepreuve)
{
    // nkhabi fih indice te3  l pays
    int np = indice_pays(pays,tabpays,*nbpays) ;
    // hadi bah nsuprimih mn tabpays w mb3d mn tabjo bsah kayn mpchkil l pays lakher yb9a m3ewd 2 marat
    for (int i =np ; np < *nbpays ; np ++){
        strcpy( tabpays[np] ,tabpays[np+1]) ;
    }
    for (int ne=0 ; ne < *nbepreuve ; ne++ )
    {
        tabjo[ne][np] = tabjo[ne][np+1];
    }
    for(int ne=0;ne<*nbepreuve;ne++){
        tabjo[ne][*nbpays] = NULL;
    }
    (*nbpays)--;
}

// 7eme procedure
void supath (string nomath, int nump,int nume, ptr tabjo[maxepreuve][maxpays])
{
    ptr  prec, p;
    p = tabjo[nume][nump];
    if (p->nom == nomath) {
        tabjo[nume][nump] = tabjo[nume][nump]->suiv;
    }
    else {
        while ((p != NULL) && (strcmp(p->nom ,nomath)))
        {
            prec = p;
            p = suivant(p);
        }
        if (p == NULL) {
            printf("Ce nom n'existe pas.\n");
        } else {
            prec->suiv = p->suiv ;
        }
    }
    liberer(p);
}


//8eme procedure tsuppremer les epreuves li mafihom hta athelethe

void suplignesvides(ptr tabjo[maxepreuve][maxpays],int nbpays,int *nbepreuve,char tabepreuve[maxepreuve][255]){
    for(int ne=0;ne< *nbepreuve;ne++){
        if(sansath(ne,tabjo,nbpays)){
            for(int i=ne;i< *nbepreuve;i++){
                for(int j=0;j<nbpays;j++){
                    tabjo[i][j] = tabjo[i+1][j];
                }
            }
            for(int i= ne ;i< *nbepreuve;i++ ){
                strcpy(tabepreuve[i],tabepreuve[i+1]);
            }
        (*nbepreuve)--;
        }
    }
}
    



int main()
{
    srand(time(0));
    int *nbpays ,np;
    np = maxpays;
    nbpays = &np;
    int *nbepreuve,ne;
    ne = maxepreuve;
    nbepreuve = &ne;
    
    char tabpays[maxpays][255];
    char tabepreuve[maxepreuve][255];
    ptr tabjo[maxepreuve][maxpays];
    creer_tabpays(tabpays);
    creer_tabepreuve(tabepreuve);
    creer_tabjo(tabjo);
   return 0;
}
