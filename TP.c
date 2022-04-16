#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "conio2.h"
// #######################    Partie declaration    ########################### //
typedef char  string[25]  ; // type de chaine de caractere

typedef struct athlethe
{
    string nom  ;
    struct athlethe *suiv ;
}athlethe ;

typedef athlethe  * ptr ; // nouveau type pour les pointeures

const unsigned MAX = 10;

const int maxpays = 150;
const int maxepreuve = 200;

// #### Machine abstraite #### //

void allouer (ptr p ) ;
ptr suivant(ptr g ) ;
void liberer(ptr p );
void aff_adr(ptr p , ptr q);
void aff_nom (ptr p , string n  );
ptr create(string tabnom[150]);
void afficher(ptr p);
int longeur(ptr p);
ptr liberer_liste(ptr tete);

// ####   Procedures de TP1   #### //

char *lower_case(char *str);//pour ne pas confondre entre le majuscule et le miniscule

void supp_blanc(char* s); // pour supprimer les blancs des textes entrees

void creer_tabnom(string tabnom[150]); //creer le tableau des noms

void creer_tabpays(char tabpays[maxpays][255]);//creer le tableau des pays

void creer_tabepreuve(char tabepreuve[maxepreuve][255]); //creer le tableau des epreuves

void creer_tabjo(ptr tabjo[maxepreuve][maxpays],string tabnom[50]); // 1ere procedure du tp

int verif_ath(string nomath,int nump, int nume, ptr tabjo[maxepreuve][maxpays]); //verifier si l'athlethe existe dans le tabjo

void inserath(string nomath , int nump ,int nume , ptr tabjo[maxepreuve][maxpays] );// inserer un athlethe

// des fonctions importants

int verif_pays (string pays , char tabpays[maxpays][255],int nbpays); // verifier si le pays existe dans tabpays

int verif_epreuve (string epreuve , char tabepreuve[maxepreuve][255],int nbepreuve); // verifier si l'epreuve exise dans tabepreuve

int indice_pays(string pays ,char tabpays[maxpays][255],int nbpays); // retoutner le numero du pays dans tabpays

int indice_epreuve(string epreuve, char tabepreuve[maxepreuve][255],int nbepreuve);// retoutner le numero de l'epreuve dans tabpays


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
int console () ; // fonction qui affiche la console et retourne le choix de l'utilisateur



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
    char pays[255];
    char epreuve[255];
    string tabnom[150];
    string nom;
    int nume,nump;
    //Creation de tabepreuve , tabpays, tabjo
    creer_tabepreuve(tabepreuve);
    creer_tabpays(tabpays);
    tab_nom(tabnom);
    creer_tabjo(tabjo,tabnom);
    // Menu principale
    int choix ;


    gotoxy(15,5);// pour afficher la console au millieu
    do
    {
         clrscr();
         choix=console();// le choix de l'utilisateur
         textcolor(WHITE);
         switch (choix)
    {
    case 1: //si l'utilisateur a choisi le premier choix
        clrscr();
       creer_tabepreuve(tabepreuve);
    creer_tabpays(tabpays);
    tab_nom(tabnom);
    creer_tabjo(tabjo,tabnom);

        gotoxy (35,3);
         textbackground(CYAN);
        printf("Creation de la matrice tabjo est en cours\n");
        gotoxy(35,5);
         textbackground(BLACK);
        for(int i=0 ; i<4 ; i++)
        {
        sleep(1);
        printf(".") ;
        }
        gotoxy(35,6);
         for(int i=0 ; i<4 ; i++)
        {
        sleep(1);
        printf(".") ;
        }
        gotoxy(35,8);
        printf("\n") ;
        gotoxy(35,9);
        printf("la matrice a ete cree avec succes !!\n");


        break;
    case 2:
        clrscr();// insertion d'un athlethe
        gotoxy(31,3);
        printf("=======================================================\n");
        gotoxy(35,5);
        textbackground(CYAN);
        printf("  Insertion d'un athlethe \n\n");
        gotoxy(35,7);
        textbackground(BLACK);
        printf("> Entrez le nom de l'athlethe -->  ");
        fgets(nom,25,stdin); // lire le nom de l'athlethe
        gotoxy(35,8);
        printf("> Entrez le nom de l'epreuve --> ");
        fgets(epreuve,255,stdin); // lire le nom de l'epreuve
        gotoxy(35,9);
        printf("> Entrez le nom du pays -->   ");
        fgets(pays,255,stdin); //lire le nom du pays
        nume = indice_epreuve(epreuve,tabepreuve,*nbepreuve);
        nump = indice_pays(pays,tabpays,*nbpays);

        printf("\n");
        if(nume > *nbepreuve) // si l'epreuve n'existe pas (chof indice epreuve / indice pays bah tzid tafham)
        {
            gotoxy(35,10);
            printf("Cet epreuve n'existe pas dans les jeux olympique\n");
        }
        else if(nump > *nbpays) // si le pays n'existe pas
        {
            gotoxy(35,10);
            printf("Ce pays n'existe pas dans les jeux olympiques\n");
        }
        else{
            printf("\n");
            inserath(nom,nump,nume,tabjo);
            gotoxy(31,wherey());
            printf("=======================================================\n");
        }
        break;
    case 3:
        clrscr();  //afficher les noms de tous les athlethes d'un pays donne
        gotoxy(35,5);
        printf("=======================================================\n");
        textbackground(CYAN) ;
        gotoxy(35,6);
        printf("  Affichage de tous les athlethes d'un pays donne \n");
        gotoxy(35,8);
        textbackground(BLACK);
        printf(" > Entrez le nom de pays -->  ");
        fgets(pays,255,stdin);
        gotoxy(35,10);
        listathpays(pays,tabpays,*nbpays,tabepreuve,*nbepreuve,tabjo);
        gotoxy(27,wherey());
        printf("========================================================\n");
        printf("\n");
        break;
    case 4 :
        clrscr();
        printf(" ==== afficher le contenu complet de la matrice tabjo  ====\n");
        listjo(tabjo,tabpays,*nbpays,tabepreuve,*nbepreuve);
        printf("=========================================================\n");
        printf("\n\n");
        getchar();
        break ;
    case 5:
        clrscr(); //supprimer pays
        gotoxy(27,4);
        printf("==================================================================\n");
        gotoxy(35,6);
        textbackground(CYAN);
        printf("   Suppression d'un pays \n");
        gotoxy(35,8);
                textbackground(BLACK);

        printf("> Entrez le nom du pays -->   ");
        fgets(pays,255,stdin);
        if(verif_pays(pays,tabpays,*nbpays)){
            suppays(pays,tabjo,tabpays,nbpays,nbepreuve);
            gotoxy(38,11);
            printf("Ce pays a ete supprime avec succes \n");
            gotoxy(27,13 );
            printf("=================================================================\n");
        }else{
            gotoxy(38,11);
            printf("Ce pays n'existe pas dans les jeux olympiques \n");
            gotoxy(27,13 );
            printf("==================================================================\n");
        }
        break;
    case 6:
        gotoxy(27,5);
        printf("==================================================================\n");
        clrscr();// supprimer athlethe
        gotoxy(35,7);
        textbackground(CYAN);
        printf("   Supression d'un athlethe \n");
        gotoxy(35,9);
                textbackground(BLACK);

        printf("> Entrez le pays de cet athlethe -->  ");

        fgets(pays,255,stdin);

        gotoxy(35,10);
        printf("> Entrez l'epreuve de cet athlethe  -->   ");

        fgets(epreuve,255,stdin);

        gotoxy(35,11);
        printf("> Entrez le nom de l'athlethe -->  ");
        fgets(nom,25,stdin);

        nume = indice_epreuve(epreuve,tabepreuve,*nbepreuve);
        nump = indice_pays(pays,tabpays,*nbpays);
        if(nume > *nbepreuve){
            gotoxy(35,13);
            printf("Cet epreuve n'existe pas dans les jeux olympiques\n");
            gotoxy(27,14);
            printf("==================================================================\n");
        }else if(nump > *nbpays){
            gotoxy(35,13);
            printf("Ce pays n'existe pas dans les jeux olympiques\n");
            gotoxy(27,14);
            printf("==================================================================\n");
        }
        else{
            gotoxy(27,13);
            supath(nom,nump,nume,tabjo);
            gotoxy(27,wherey());
            printf("==================================================================\n");
        }
        break;
    case 7:
        clrscr(); // supprimer toutes les épreuves pour lesquelles aucune inscription n’a été enregistrée.
        gotoxy(27,5);
         printf("=========================================================================\n");
         textbackground(CYAN);
                 gotoxy(20,7);


        printf("Suppression de toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree \n");
        textbackground(BLACK);
        gotoxy (35,9);
        for(int i=0 ; i<4 ; i++)
        {
        sleep(1);
        printf(".") ;
        }
        gotoxy(35,10);
         for(int i=0 ; i<4 ; i++)
        {
        sleep(1);
        printf(".") ;
        }
        suplignesvides(tabjo,*nbpays,nbepreuve,tabepreuve);
        gotoxy(18,12);
        printf("toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree ont ete supprimees \n");
        gotoxy(27,14);
        printf("==========================================================================\n");
        getchar();
        break;
    case 8:
        clrscr(); //Quitter
        gotoxy(35,12);
        printf(" Merci d'avoir bien utiliser notre programme \n ");
        break;
    }
    printf("\n\n");
    if(choix != 8){
        getchar();
    }
    } while (choix != 8);
   return 0;
}

void allouer (ptr p )
{
    p = malloc(sizeof(athlethe));
    p->suiv =NULL ;
}

ptr suivant(ptr g )
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

ptr create(string tabnom[50])
{

    ptr tete,tmp,nouv ;
    int n,m ;
    n = rand() % 11 ;
    m = rand() % 140 ;
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


void afficher(ptr p) // afficher la liste des athlethes
{
    ptr tmp ;//pointeur tomporaire
    tmp = p ;
    while ( tmp != NULL)
    {
        gotoxy(35,wherey());
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

char *lower_case(char *str){
    for(int i= 0;str[i];i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

void supp_blanc(char* s) {
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}


//construire tableau tabnom
void tab_nom(string tabnom[150])
{
    FILE *f = fopen("noms","r") ;
    string nom;
    for ( int i =0 ; i < 150 ; i++)
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
//1 ere procedure creer tabjo

void creer_tabjo(ptr tabjo[maxepreuve][maxpays],string tabnom[150])
{
    for(int i=0;i< maxepreuve;i++){
        for(int j=0;j<maxpays;j++){
            tabjo[i][j] = create(tabnom);
        }
    }
}



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
// 2eme procedure

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
        gotoxy(35,11);
        printf("la nouvelle liste des athlethes : \n");
        gotoxy(35,13);
        afficher(tabjo[nume][nump]);
    }else if (longeur(tabjo[nume][nump]) == 10)
    {
        gotoxy(30,10) ;
        printf("Il y a deje 10 athletes inscrits, vous ne pouvez pas inserer un autre athlete!\n");
        printf("\n");
    }else{
        gotoxy(35,10);
        printf("il y a deja un athlethe inscrit avec ce nom.\n");
        printf("\n");
    }
}

int verif_pays (char pays[255] , char tabpays[maxpays][255],int nbpays)
{
    int trouv = 0;
    char str[255];
    supp_blanc(pays);
    strcpy(pays,lower_case(pays));
    for (int i = 0 ; i < nbpays; i++)
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

int verif_epreuve (char epreuve[255] , char tabepreuve[maxepreuve][255],int nbepreuve)
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



int indice_pays(char pays[255] ,char tabpays[maxpays][255],int nbpays)
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

int indice_epreuve(char epreuve[255], char tabepreuve[maxepreuve][255],int nbepreuve)
{


    char str[255];
        strcpy(epreuve,lower_case(epreuve));
        supp_blanc(epreuve);
        for (int i = 0; i < nbepreuve; i++)
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
    int trou = 0 ;
    if (verif_pays(pays,tabpays,nbpays))
    {
   int p =  indice_pays(pays,tabpays,nbpays); // on stocke l 'indice du pays dans p
   for (int i=0 ; i<nbepreuve ; i ++)
   {
       if (tabjo[i][p] != NULL) {
            gotoxy(20,wherey()); // pour l'affichage
           printf("%s", tabepreuve[i]); //afficher l'epreuve
           gotoxy(20,wherey());
           printf("=============================================\n");
                      gotoxy(20,wherey());

           printf("les athlethes sont\n");
           afficher(tabjo[i][p]);// afficher la liste
           trou = 1 ; // on a trouve au moins une seule  epreuve
       }
   }
   if ( trou == 0 ) printf(" ce pays n'aucun concurrent \n")  ; // le pays existe mais il n'a aucun athlethe inscrit dans cette epreuve
   }
    else{
            printf("%d",(verif_pays(pays,tabpays,nbpays))) ;
        printf("Ce pays n'existe pas dans les jeux olympiques\n") ; // l ism li dkhlto ghalt
        printf("\n");
    }
}

// 4eme procedure
int sansath(int ne , ptr tabjo[maxepreuve][maxpays],int nbpays )
{
    int np ;
    int trouv = 1;
    for (np = 0 ; np <nbpays; np ++ ) // on parcoure les pays
    {
        if (tabjo[ne][np] != NULL ){ // si il n'y a aucun athlethe inscrit
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
                    printf("Ce pay n'a aucun athlethe dans l'epreuve %s\n",tabepreuve[j]);
                }else{
                    afficher(tabjo[i][j]);
                }
                printf("------------------------------------\n");
            }
        }
    }
}

//6eme procedure
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
    if (!(strcmp(p->nom ,nomath))) {
        tabjo[nume][nump] = tabjo[nume][nump]->suiv;
         printf("\Ce athlethe a ete supprime\n");
;
        printf("la nouvelle liste des athlethes \n");
        afficher(tabjo[nume][nump]);

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

        printf("\Ce athlethe a ete supprime\n");
        printf("la nouvelle liste des athlethes \n");
        afficher(tabjo[nume][nump]);
        }
    }
    liberer(p);
}


//8eme procedure tsuppremer les epreuves li mafihom hta athelethe

void suplignesvides(ptr tabjo[maxepreuve][maxpays],int nbpays,int *nbepreuve,char tabepreuve[maxepreuve][255]){
    for(int ne=0;ne< *nbepreuve;ne++){ // on parcoure la liste des epreuves
        if(sansath(ne,tabjo,nbpays)){ // si cette epreuve n'a aucun athlethe inscrit on la supprime
            for(int i=ne;i< *nbepreuve;i++){
                for(int j=0;j<nbpays;j++){
                    tabjo[i][j] = tabjo[i+1][j]; // on la remplace par l'epreuve suivante
                }
            }
            for(int i= ne ;i< *nbepreuve;i++ ){
                strcpy(tabepreuve[i],tabepreuve[i+1]);
            }
        (*nbepreuve)--;
        }
    }
}


void down(int x ,int y)
{

    gotoxy(x,y+2);


}

void up(int x , int y )
{
     gotoxy(x,y-2);


}
int console()
{
  gotoxy(15,4) ;
  textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor(LIGHTRED);
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
   textcolor(LIGHTBLUE);
   printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
        textbackground(LIGHTRED) ;
        textcolor(WHITE);

    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");
        textbackground(BLACK) ;
     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
        gotoxy(15,8) ;

        while(1 )
        {
        int y = wherey() ;
int         z = getch() ;
        switch (y)
        {
        case 8  :
            if ( z == 13)
            {
                return 1 ;
                break ;
            }
            if (z == 0x50)
            {
         clrscr();
          gotoxy(15,4) ;
          textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
textcolor (WHITE );

    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");
     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
     textbackground(LIGHTRED) ;
    printf("#2. Inserer une athlethe\n");
    textbackground(BLACK);
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
        gotoxy(15,10);
            }
            else if ( z == 0x48)
            {
         clrscr();
    gotoxy(15,4) ;
    textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
textcolor (WHITE );
    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");
     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
      textbackground(LIGHTRED);
    printf("#8. Quitter le programme \n");
    textbackground(BLACK) ;
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         gotoxy(14,22);
            }
            break ;
        case 10 :
            if ( z == 13 )
            {
                return 2 ;
                break ;
            }
               if (z == 0x50)
            {
        gotoxy(15,4) ;
        textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
        textcolor (WHITE );
    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");
     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
        textbackground(LIGHTRED) ;
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
        textbackground(BLACK);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
        gotoxy(15,4) ;
        textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
        textcolor (WHITE );
        textbackground(LIGHTRED) ;

    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");
        textbackground(BLACK) ;
     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         up(14,y);
            }
            break ;
        case 12 :
            if ( z == 13 )
            {
                 return 3 ;
                 break ;
            }
         if (z == 0x50)
            {
         clrscr();
        gotoxy(15,4) ;
        textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
        textcolor (WHITE );

    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");
     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);

    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
    textbackground(LIGHTRED);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
         textbackground(BLACK) ;
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
        gotoxy(15,4) ;
        textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
        textcolor (WHITE );


    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");

     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
     textbackground(LIGHTRED) ;
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
        textbackground(BLACK) ;
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         up(14,y);
            }
break ;

  case 14 :
      if ( z == 13)
            {
                 return 4 ;
                 break ;
            }
if (z == 0x50)
            {
         clrscr();
         gotoxy(15,4) ;
         textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        textcolor (WHITE);
        printf("\n");
        gotoxy(15,8);
    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");
     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
         textbackground(LIGHTRED);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
        textbackground(BLACK);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
       gotoxy(15,4) ;
       textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);

      textcolor (WHITE );
    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");

     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
        textbackground(LIGHTRED) ;
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
        textbackground(BLACK) ;
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         up(14,y);
            }
            break ;

             case 16 :
                 if ( z == 13 )
            {
                 return 5 ;
                 break ;
            }
if (z == 0x50)
            {
         clrscr();
 gotoxy(15,4) ;
 textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
textcolor (WHITE);

    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");

     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
        textbackground(LIGHTRED) ;
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
         textbackground(BLACK) ;
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
       gotoxy(15,4) ;
       textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);

textcolor (WHITE);
    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");

     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
        textbackground(LIGHTRED) ;
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
         textbackground(BLACK) ;
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         up(14,y);
            }

        break ;
case 18 :
    if ( z == 13 )
            {
                 return 6 ;
                 break ;
            }
if (z == 0x50)
            {
         clrscr();
 gotoxy(15,4) ;
 textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);

textcolor (WHITE );
    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");

     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
         textbackground(LIGHTRED) ;
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
      textbackground(BLACK) ;
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
       gotoxy(15,4) ;
       textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
textcolor (WHITE);

    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");

     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
         textbackground(LIGHTRED) ;
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
        textbackground(BLACK) ;
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         up(14,y);
        }
        break ;
case 22 :
    if ( z == 13 )
            {
                 return 8 ;
                 break ;
            }
    if (z == 0x50)
            {
         clrscr();
        gotoxy(15,4) ;
        textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
    textcolor (WHITE );
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
    textbackground(LIGHTRED);

    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");

     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
     textbackground(BLACK);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);

    printf("#8. Quitter le programme \n");

    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         gotoxy(14,8);
            }
            else if ( z == 0x48)
            {
         clrscr();
      gotoxy(15,4) ;
      textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);
textcolor (WHITE );

    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");

     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
       ;
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
          textbackground(LIGHTRED) ;

    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
      textbackground(BLACK) ;
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         up(14,y);
            }
            break ;
            case 20 :
    if ( z == 13 )
            {
                 return 7 ;
                 break ;
            }
    if (z == 0x50)
            {
         clrscr();
        gotoxy(15,4) ;
        textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED );
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);

textcolor (WHITE );
    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");

     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
      textbackground(LIGHTRED) ;
    printf("#8. Quitter le programme \n");
    textbackground(BLACK) ;
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         down(14,y);
            }
            else if ( z == 0x48)
            {
         clrscr();
      gotoxy(15,4) ;
      textcolor (LIGHTBLUE );
   printf("========================================================================================\n");
   gotoxy(48,5);
   textcolor (LIGHTRED);
   printf("Welcome to Paris 2024\n");
    gotoxy(15,6);
    textcolor (LIGHTBLUE );
    printf("========================================================================================\n");
        gotoxy(15,7);
        printf("\n");
        gotoxy(15,8);

textcolor (WHITE );
    printf("#1.Creer tabjo contenant les noms de tous les athletes de tous les pays dans toutes les epreuves\n");

     gotoxy(15,9) ;
     printf("\n");
     gotoxy(15,10);
    printf("#2. Inserer une athlethe\n");
    gotoxy(15,11);
     printf("\n");
        gotoxy(15,12);
    printf("#3. Afficher les noms de tous les athlethes d'un pays donne\n");
    gotoxy(15,13);
     printf("\n");
        gotoxy(15,14);
    printf("#4. Afficher le contenu complet de la matrice tabjo epreuve par epreuve\n");
    gotoxy(15,15);
     printf("\n");
         gotoxy(15,16);
    printf("#5. Supprimer un pays pour des raisons budgetaires ou politiques\n");
    gotoxy(15,17);
     printf("\n");
        gotoxy(15,18);
        textbackground(LIGHTRED) ;
    printf("#6. Supprimer un athlethe disqualifie ou blesse\n");
    gotoxy(15,19);
     printf("\n");
         gotoxy(15,20);
         textbackground(BLACK) ;
    printf("#7. Supprimer toutes les epreuves pour lesquelles aucune inscription n'a ete enregistree\n");
    gotoxy(15,21);
     printf("\n");
      gotoxy(15,22);
    printf("#8. Quitter le programme \n");
    gotoxy(15,23);
     printf("\n");
        gotoxy(15,24);
        textcolor (LIGHTBLUE );
        printf("========================================================================================\n");
         up(14,y);
            }
            break ;


}
}
}
