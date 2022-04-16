#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "conio2.h"

// #######################    Partie declaration    ########################### //
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

// #### Machine abstraite #### //

void allouer (ptr p ) ;
ptr suivant(ptr g ) ;
void liberer(ptr p );
void aff_adr(ptr p , ptr q);
void aff_nom (ptr p , string n  );
ptr create(string tabnom[50]);
void afficher(ptr p);
int longeur(ptr p);
ptr liberer_liste(ptr tete);

// ####   Procedure de TP1   #### //
char *lower_case(char *str);
void supp_blanc(char* s);
void tab_nom(string tabnom[50]);
void creer_tabpays(char tabpays[maxpays][255]);
void creer_tabepreuve(char tabepreuve[maxepreuve][255]);
// 1 er procedure
void creer_tabjo(ptr tabjo[maxepreuve][maxpays],string tabnom[50]);

int verif_ath(string nomath,int nump, int nume, ptr tabjo[maxepreuve][maxpays]);
// 2 eme procedure
void inserath(string nomath , int nump ,int nume , ptr tabjo[maxepreuve][maxpays] );
// des fonctions importants
int verif_pays (string pays , char tabpays[maxpays][255],int nbpays);
int verif_epreuve (string epreuve , char tabepreuve[maxepreuve][255],int nbepreuve);
int indice_pays(string pays ,char tabpays[maxpays][255],int nbpays);
int indice_epreuve(string epreuve, char tabepreuve[maxepreuve][255],int nbepreuve);

// 3 eme procedure
void listathpays(string pays , char tabpays[maxpays][255] ,int nbpays, char tabepreuve [maxepreuve][255] ,int nbepreuve, ptr tabjo[maxepreuve][maxpays]);
// 4 eme procedure
int sansath(int ne , ptr tabjo[maxepreuve][maxpays],int nbpays );
// 5 eme procedure
void listjo(ptr tabjo[maxepreuve][maxpays],char tabpays[maxpays][255],int nbpays,char tabepreuve[maxepreuve][255],int nbepreuve);
// 6 eme procedure
void suppays (string pays , ptr tabjo[maxepreuve][maxpays] ,char tabpays[maxpays][255] ,int *nbpays,int *nbepreuve);
// 7 eme procedure
void supath (string nomath, int nump,int nume, ptr tabjo[maxepreuve][maxpays]);
// 8 eme procedure
void suplignesvides(ptr tabjo[maxepreuve][maxpays],int nbpays,int *nbepreuve,char tabepreuve[maxepreuve][255]);

//   Menu principale
int menu();
int console () ;



int main()
{
    srand(time(0));
    //declaration des variables
    char tabpays[maxpays][255];
    char tabepreuve[maxepreuve][255];
    ptr tabjo[maxepreuve][maxpays];
    int *nbepreuve,*nbpays;
    int a = maxepreuve,b = maxpays;
    nbepreuve = &a;
    nbpays = &b;
    char pay[255];
    char epreuve[255];
    string tabnom[50];
    string nom;
    int nume,nump;
    //Creation de tabepreuve , tabpays, tabjo
    creer_tabepreuve(tabepreuve);
    creer_tabpays(tabpays);
    tab_nom(tabnom);
    creer_tabjo(tabjo,tabnom);
    // Menu principale
    int choie ;
    int z,choix ;

    gotoxy(15,5);



    do
    {
         clrscr();
         choix=console();
         switch (choix)
    {
    case 1: // afficher kamel les athelethe ta3 kamel les epreuves w kamel les pays
        clrscr();
        printf("  ## afficher le contenu complet de la matrice tabjo  ##\n");
        listjo(tabjo,tabpays,*nbpays,tabepreuve,*nbepreuve);
        printf("=========================================================\n");
        printf("\n\n");
        getchar();
        break;
    case 2:
        clrscr();// insertion d'un athlethe
        printf("  ## Insertion d'un athlethe ##\n\n");
        printf("> Entrez le nom d'athlethe -->  ");
        getchar();
        fgets(nom,25,stdin);
        printf("> Entrez le nom d'epreuve --> ");
        fgets(epreuve,255,stdin);
        printf("> Entrez le nom de pay -->   ");
        fgets(pay,255,stdin);
        nume = indice_epreuve(epreuve,tabepreuve,*nbepreuve);
        nump = indice_pays(pay,tabpays,*nbpays);
        printf("\n");
        if(nume > *nbepreuve) // si l'epreuve n'existe pas (chof indice epreuve / indice pays bah tzid tafham)
        {
            printf("Ce epreuve n'existe pas dans les jeux olympique\n");
        }else if(nump > *nbpays) // si le pay n'existe pas
        {
            printf("Ce pay n'existe pas dans les jeux olympiques\n");
        }else{
            printf("\n");
            inserath(nom,nump,nume,tabjo);
        }
        break;
    case 3:
        clrscr();  //afficher les noms de tous les athlethes d'un pays donne
        printf("  ## Affichage de tous les athlethes d'un pays donnes  ##\n");
        printf("> Entrez le nom de pay -->  ");
        getchar();
        fgets(pay,255,stdin);
        listathpays(pay,tabpays,*nbpays,tabepreuve,*nbepreuve,tabjo);
        printf("===================================================\n");
        printf("\n");
        break;
    case 4:
        clrscr(); //supprimer pay
        printf("  ## Suppression d'une pay ##\n");
        printf("> Entrez le nom de pay -->   ");
        getchar();
        fgets(pay,255,stdin);
        if(verif_pays(pay,tabpays,*nbpays)){
            suppays(pay,tabjo,tabpays,nbpays,nbepreuve);
            printf("Ce pays a été supprimé\n");
            printf("=====================================================\n");
        }else{
            printf("Ce pays n'existe pas dans les jeux olimpiques\n");
            printf("===========================================================\n");
        }
        break;
    case 5:
        clrscr();// supprimer athlethe
        printf("  ## Supression d'un athlethe ##\n");
        printf("> Entrez le nom d'athlethe -->  ");
        getchar();
        fgets(nom,25,stdin);
        printf("> Entrez le pay de ce athlethe -->  ");
        fgets(pay,255,stdin);
        printf("> Entrez l'epreuve de ce athlethe  -->   ");
        fgets(epreuve,255,stdin);
        nume = indice_epreuve(epreuve,tabepreuve,*nbepreuve);
        nump = indice_pays(pay,tabpays,*nbpays);
        if(nume > *nbepreuve){
            printf("Ce epreuve n'existe pas dans les jeux olympiques\n");
            printf("=====================================================\n");
        }else if(nump > *nbpays){
            printf("Ce pay n'existe pas dans les jeux olympiques\n");
            printf("=====================================================\n");
        }else{
            supath(nom,nump,nume,tabjo);
            printf("=================================================\n");
        }
        break;
    case 6:
        clrscr(); // supprime toutes les épreuves pour lesquelles aucune inscription n’a été enregistrée.
        printf("  ## Suppression de toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree ##\n");
        suplignesvides(tabjo,*nbpays,nbepreuve,tabepreuve);
        printf("\ntoutes les epreuves pour lesquelles aucune inscription n'a ete enregistrer ont ete supprime\n");
        printf("==================================================================\n");
        getchar();
        break;
    case 7:
        clrscr(); //Quitter
        printf("   ##  Quitter le programme  ##\n");
        break;
    }
    printf("\n\n");
    if(choie != 7){
        printf("> Appuyez sur Enter pour affichier le menu\n\n");
        getchar();
    }
    } while (choix != 7);
   return 0;
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
ptr create(string tabnom[50])
{

    ptr tete,tmp,nouv ;
    int n,m ;
    n = rand() % 11 ;
    m = rand() % 40 ;
    tete = NULL ;
    for (int i=0 ; i< n ; i++ )
    {
        nouv = malloc(sizeof(athlethe));
        nouv->suiv =NULL ;
        strcpy(nouv->nom, tabnom[m]);
        m++ ;
        if ( tete==NULL)
        {
            tete = nouv ;
            tmp = nouv ;
        }
        else {
            tmp->suiv = nouv;
            tmp = nouv;
        }
    nouv = NULL;
    }

    return tete ;
}


void afficher(ptr p)
{
    ptr tmp ;
    tmp = p ;
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

// hadi fonction tliberer tous les element ta3 la liste w traje3let 'NULL'
ptr liberer_liste(ptr tete){
    if(tete != NULL){
        ptr proc,p;
        p = tete;
        tete = NULL;
        proc = p->suiv;
        while (proc != NULL)
        {
            free(p);
            p = proc;
            proc = p->suiv;
        }
        free(p);
    }
    return tete;
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


//construire tableau tabnom
void tab_nom(string tabnom[50])
{
    FILE *f = fopen("noms","r") ;
    string nom;
    for ( int i =0 ; i < 50 ; i++)
    {
        fgets(nom,25,f);
        strcpy(nom,lower_case(nom));
        nom[0] = toupper(nom[0]);
        strcpy(tabnom[i],nom);
    }
    fclose(f);
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

void creer_tabjo(ptr tabjo[maxepreuve][maxpays],string tabnom[50])
{
    for(int i=0;i< maxepreuve;i++){
        for(int j=0;j<maxpays;j++){
            tabjo[i][j] = create(tabnom);
        }
    }
}


//hadi fonction tverifier ida nom ath yexister f liste (True) w la non (False)
int verif_ath(string nomath,int nump, int nume, ptr tabjo[maxepreuve][maxpays]){
    int b = 0;
    ptr tmp = tabjo[nume][nump];
    supp_blanc(nomath);
    while (tmp != NULL)
    {
        if(!strcmp(((*tmp).nom),nomath)){
            b = 1;
            return b;
        }
        tmp = tmp->suiv;
    }
    return b;

}
// 2eme procedure (modifier)

void inserath(string nomath , int nump ,int nume , ptr tabjo[maxepreuve][maxpays] )
{
    ptr tmp = tabjo[nume][nump] ;
    strcpy(nomath,lower_case(nomath));
    nomath[0] = toupper(nomath[0]);
    if((!verif_ath(nomath,nump,nume,tabjo)) && (longeur(tabjo[nume][nump]) < 10)) //Si nom ath n'exite pas et la longeur t3 liste < 10 donc inserer ath
    {
        ptr ath = malloc(sizeof(athlethe)); //new maillon
        aff_nom(ath,nomath);
        aff_adr(ath,tabjo[nume][nump]);// aff_adr m3a la tete de liste
        tabjo[nume][nump] = ath;  // la nouveau tete est le nouveau maillon.
        printf("la nouvelle list des athlethes \n");
        afficher(tabjo[nume][nump]);
    }else if (longeur(tabjo[nume][nump]) == 10)
    {
        printf("Il y a déjà 10 athlètes inscrits, vous ne pouvez pas inserer un autre athlète!\n");
        printf("\n");
    }else{
        printf("il y a deja un athlethe inscrit avec ce nom.\n");
        printf("\n");
    }
}

int verif_pays (char pays[255] , char tabpays[maxpays][255],int nbpays) // tgolk ida kayn had l pays wla non
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

int verif_epreuve (char epreuve[255] , char tabepreuve[maxepreuve][255],int nbepreuve) // tgolk ida kayn l'epreuve li d5ltha wla non  wla non
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



int indice_pays(char pays[255] ,char tabpays[maxpays][255],int nbpays) // tmdlha ism bled tmdlk numero te3o
{
        char str[255];
        strcpy(pays,lower_case(pays));
        supp_blanc(pays);
        for (int i = 0; i < nbpays; i++)
        {
            strcpy(str,tabpays[i]);
            supp_blanc(str);
            if (!(strcmp(str, pays)))
                return i;
        }
        return (maxpays +1);
}

int indice_epreuve(char epreuve[255], char tabepreuve[maxepreuve][255],int nbepreuve) // wla epreuve nfs lkhdma galna t9dro tzido parametre
{
        char str[255];
        strcpy(epreuve,lower_case(epreuve));
        supp_blanc(epreuve);
        for (int i = 0; i < nbepreuve; i++)   // mlgitch kifah ndkhl tabpays psa mahoch parametre
        {
            strcpy(str,tabepreuve[i]);
            supp_blanc(str);
            if (!(strcmp(str, epreuve)))
                return i;
        }
        return(maxepreuve +1);
}


 // 3eme procedure

void listathpays(char pays[255] , char tabpays[maxpays][255] ,int nbpays, char tabepreuve [maxepreuve][255] ,int nbepreuve, ptr tabjo[maxepreuve][maxpays])
{
    int trouv = 0 ;
    if (verif_pays(pays,tabpays,nbpays))
    {
   int p =  indice_pays(pays,tabpays,nbpays); // on stocke l 'indice te3 lpays f p
   for (int i=0 ; i<nbepreuve ; i ++)
   {
       if (tabjo[i][p] != NULL) {
           printf("%s", tabepreuve[i]); //afficher l'epreuve
           printf("=============================================\n");
           printf("les athlethes sont\n");
           afficher(tabjo[i][p]);// afficher la liste
           trouv = 1 ; // m3naha lgina au moins epreuve wahda
       }
   }
   if ( trouv == 0 ) printf(" ce pays n'aucun concurrent \n")  ; // kayn f tabpays bsah m3ndoch athlethe
   }
    else{
        printf("Ce pays n'existe pas dans les jeux olympiques\n") ; // l ism li dkhlto ghalt
        printf("\n");
    }
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
                    printf("Ce pay n'a aucun athlethe en l'epreuve %s\n",tabepreuve[j]);
                }else{
                    afficher(tabjo[i][j]);
                }
                printf("------------------------------------\n");
            }
        }
    }
}

//6eme procedure li tsuprimi
void suppays (char pays[255] , ptr tabjo[maxepreuve][maxpays] ,char tabpays[maxpays][255] ,int *nbpays,int *nbepreuve)
{
    // nkhabi fih indice te3  l pays
    int np = indice_pays(pays,tabpays,*nbpays) ;
    // hadi bah nsuprimih mn tabpays w mb3d mn tabjo bsah kayn mpchkil l pays lakher yb9a m3ewd 2 marat
    for (int i =np ; i< *nbpays ; i ++){
        strcpy( tabpays[i] ,tabpays[i+1]) ;
    }

    for(int ne=0;ne<*nbepreuve;ne++){
        tabjo[ne][np] = liberer_liste(tabjo[ne][np]);
    }
    (*nbpays)--;
    for(int i= np;i<*nbpays;i++){
        for (int ne=0 ; ne < *nbepreuve ; ne++ ){
        tabjo[ne][i] = tabjo[ne][i+1];
    }
    }
}

// 7eme procedure
void supath (string nomath, int nump,int nume, ptr tabjo[maxepreuve][maxpays])
{
    ptr  prec, p;
    p = tabjo[nume][nump];

    strcpy(nomath,lower_case(nomath));
    nomath[0] = toupper(nomath[0]);
    supp_blanc(nomath);
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
            printf("\nCe athlethe n'existe pas dans cette liste\n");
        } else {
            prec->suiv = p->suiv ;
            printf("\nCe athlethe a ete supprime\n");
        printf("la nouvelle list des athlethes \n");
        afficher(tabjo[nume][nump]);
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

// Menu principale
int menu(){
    printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
    printf("========================================================================\n");
    printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
    printf("#2. Inserer une athlethe\n");
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    printf("#4. Supprimer une pays a cause des raisons politiques\n");
    printf("#5. supprimer un athlète disqualifié ou blesse\n");
    printf("#6. supprime toutes les épreuves pour lesquelles aucune inscription n' a étéenregistrée.\n");
    printf("#7. Quitter le programme\n");
    printf("========================================================================\n");
    int choix;
    do
    {
        printf("Entrez votre choix  -->  ");
        scanf("%d",&choix);
        if((choix <1 ) || (choix > 7)){
            printf("Vous devez entrer un entier entre 1 et 7\n");
        }
    } while ((choix < 1) ||(choix > 7));
    printf("==========================================================================\n");
    return choix;
}
void down(int x ,int y)
{

    gotoxy(x,y+1);


}

void up(int x , int y )
{
     gotoxy(x,y-1);


}
int console()
{
 printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
    gotoxy(15,6);
    printf("========================================================================\n");
        gotoxy(15,7);
        textbackground(GREEN) ;
    printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
        textbackground(BLACK) ;
        gotoxy(15,8);
    printf("#2. Inserer une athlethe\n");
        gotoxy(15,9);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
        gotoxy(15,10);
    printf("#4. Supprimer une pays a cause des raisons politiques\n");
        gotoxy(15,11);
    printf("#5. supprimer un athlète disqualifié ou blesse\n");
        gotoxy(15,12);
    printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
        gotoxy(15,13);
    printf("#7. Quitter le programme\n");
        gotoxy(15,14);
    printf("========================================================================\n");
        gotoxy(15,7);

        while(1 )
        {
        int y = wherey() ;
int         z = getch() ;
        switch (y)
        {
        case 7  :
            if ( z == 13)
            {
                return 1 ;
                break ;
            }
            if (z == 0x50)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);
         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
         textbackground(GREEN) ;
         printf("#2. Inserer une athlethe\n");
                  textbackground(BLACK) ;
         gotoxy(15,9);
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);
         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);
         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
         printf("#2. Inserer une athlethe\n");
         gotoxy(15,9);
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);
         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         textbackground(GREEN) ;
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         textbackground(BLACK);
         printf("========================================================================\n");
         gotoxy(14,13);
            }
            break ;
        case 8 :
            if ( z == 13 )
            {
                return 2 ;
                break ;
            }
               if (z == 0x50)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);
         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
         printf("#2. Inserer une athlethe\n");
         textbackground(GREEN) ;
         gotoxy(15,9);
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         textbackground(BLACK) ;
         gotoxy(15,10);
         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);
                 textbackground(GREEN) ;

         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
                 textbackground(BLACK);

         printf("#2. Inserer une athlethe\n");
         gotoxy(15,9);
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);
         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         up(14,y);
            }
            break ;
        case 9 :
            if ( z == 13 )
            {
                 return 3 ;
                 break ;
            }
         if (z == 0x50)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);
         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
         printf("#2. Inserer une athlethe\n");

         gotoxy(15,9);
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);
                  textbackground(GREEN) ;

         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
                  textbackground(BLACK) ;

         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);


         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
          textbackground(GREEN) ;

         printf("#2. Inserer une athlethe\n");
         gotoxy(15,9);
         textbackground(BLACK) ;
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);
         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         up(14,y);
            }
break ;

  case 10 :
      if ( z == 13)
            {
                 return 4 ;
                 break ;
            }
if (z == 0x50)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);
         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
         printf("#2. Inserer une athlethe\n");
         gotoxy(15,9);
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);
         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
         textbackground(GREEN) ;
         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         textbackground(BLACK) ;
         gotoxy(15,12);
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);


         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);

         printf("#2. Inserer une athlethe\n");
         gotoxy(15,9);
                           textbackground(GREEN) ;

         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);
                           textbackground(BLACK) ;

         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         up(14,y);
            }
            break ;

             case 11 :
                 if ( z == 13 )
            {
                 return 5 ;
                 break ;
            }
if (z == 0x50)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);
         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
         printf("#2. Inserer une athlethe\n");

         gotoxy(15,9);
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);

         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);

         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
                           textbackground(GREEN) ;

         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
                           textbackground(BLACK) ;

         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);


         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);

         printf("#2. Inserer une athlethe\n");
         gotoxy(15,9);

         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);
                           textbackground(GREEN) ;

         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
                                    textbackground(BLACK) ;

         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         up(14,y);
            }

        break ;
case 12 :
    if ( z == 13 )
            {
                 return 6 ;
                 break ;
            }
if (z == 0x50)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);
         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
         printf("#2. Inserer une athlethe\n");

         gotoxy(15,9);
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);

         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);

         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);


         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
                           textbackground(GREEN) ;

         printf("#7. Quitter le programme\n");
         textbackground(BLACK) ;
         gotoxy(15,14);
         printf("========================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);


         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);

         printf("#2. Inserer une athlethe\n");
         gotoxy(15,9);

         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);


         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
                                    textbackground(GREEN) ;

         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
          textbackground(BLACK) ;
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         up(14,y);
        }
        break ;
case 13 :
    if ( z == 13 )
            {
                 return 7 ;
                 break ;
            }
    if (z == 0x50)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);
         textbackground(GREEN) ;
         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
         textbackground(BLACK) ;
         printf("#2. Inserer une athlethe\n");
         gotoxy(15,9);
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);
         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);
         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         gotoxy(14,7);
            }
            else if ( z == 0x48)
            {
         clrscr();
         gotoxy(15,5);
         printf("Choisissez dans la liste suivante l'opération que vous souhaitez effectuer\n");
         gotoxy(15,6);
         printf("========================================================================\n");
         gotoxy(15,7);
         printf("#1. Affichier tous les athlethes de tous les epreuves et les pays\n");
         gotoxy(15,8);
         printf("#2. Inserer une athlethe\n");
         gotoxy(15,9);
         printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
         gotoxy(15,10);

         printf("#4. Supprimer une pays a cause des raisons politiques\n");
         gotoxy(15,11);

         printf("#5. supprimer un athlète disqualifié ou blesse\n");
         gotoxy(15,12);
         textbackground(GREEN) ;
         printf("#6. supprime toutes les epreuves pour lesquelles aucune inscription n' a ete enregistree.\n");
         gotoxy(15,13);
         textbackground(BLACK) ;
         printf("#7. Quitter le programme\n");
         gotoxy(15,14);
         printf("========================================================================\n");
         up(14,y);
            }
            break ;


}
}
}
