#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/*@require: pointeur du type 'char' NOT NULL
  @assigns: rien
  @ensure : retour 1 si p contient seulement chiffre retour 0 sinon
*/
int isnumber(char* p)
{
    for ( ; *p ; p+=1 )
        if ( *p<'0' || '9'<*p )
            return 0;
    return 1;
    }



/*
    @param: la taille de grille
    @retuen: la pointeur de grille
*/
int** newGrille(int taille){
    int** grille = (int**)calloc(taille,sizeof(int*));
    int i;
    for(i=0 ; i<taille; i++){
        grille[i]=(int*) calloc(taille,sizeof(int));
    }
    return grille;
}

/*
    @param: la pointeur de grille,la taille de grille
    @retuen: rien
*/
void freeGrille(int** grille,int taille){
    int i;
    for (i=0;i<taille;i++){
        free((void*)grille[i]);
    }
    free((void*)grille);
}

/*
    @param: la pointeur de grille,la taille de grille
    @retuen: la grille avec l'initialisation à partir de valeurs aléatoires
*/
void iniGrille(int** grille,int taille){
    int i,j,ran;
    srand((unsigned)time(NULL));
    for(i=0;i<taille;i++){
        for(j=0;j<taille;j++){

            ran = rand()%6 + 1;
            grille[i][j]=ran;
        }
    }
}

/*
    @param: la pointeur de grille,la taille de grille, coordonneee (x,y), color
    @retuen: la grille apres la changement.
*/
void rempalcer (int** grille, int taille, int x, int y, int color){
    if(x>=taille||y>=taille){
        printf("Wrong coordonnee");
        exit(1);
    }else{
        grille[x][y]=color;
    }
}
/*
    @param: la pointeur de grille,la taille de grille
    @retuen: rien
*/
void afficher(int** grille,int taille){
    int i,j;
    for(i=0;i<taille;i++){
        printf("\n");
        for(j=0;j<taille;j++){
            printf(" %d ",grille[i][j]);
        }
    }
    printf("\n");
}


/*
    @param: la pointeur de grille,le couleur d'origine,la taille de grille,coordonneee (x,y),la changement de couleur
    @retuen: void
*/
void changer(int** grille,int colorOrigin, int taille, int x, int y,int color){
    if(colorOrigin!=color){
        if((x>=0)&&(x<taille)&&(y>=0)&&(y<taille)){
            if(grille[x][y]==colorOrigin){
                grille[x][y]=color;
                if((x==0)&&(y==0)){
                    changer(grille,colorOrigin,taille,x+1,y,color);
                    changer(grille,colorOrigin,taille,x,y+1,color);
                }else if((x==taille-1)&&(y==taille-1)){
                    changer(grille,colorOrigin,taille,x-1,y,color);
                    changer(grille,colorOrigin,taille,x,y-1,color);
                }else{
                    changer(grille,colorOrigin,taille,x+1,y,color);
                    changer(grille,colorOrigin,taille,x,y+1,color);
                    changer(grille,colorOrigin,taille,x-1,y,color);
                    changer(grille,colorOrigin,taille,x,y-1,color);
                }
            }
        }
    }
}


/*
    @param: la pointeur de grille,la taille de grille,,la changement de couleur
    @retuen: void
*/
void initChanger(int** grille, int taille, int color){
    int colorOrigin = grille[0][0];
    grille[0][0]=color;
    changer(grille,colorOrigin,taille,0,1,color);
    changer(grille,colorOrigin,taille,1,0,color);
}


/*
    @param: la pointeur de grille,la taille de grille
    @retuen: un fichier qui contient la grille
*/
void createFichier(int** grille,int taille){
  int i,j,r;
  char* nom = (char*) malloc(100*sizeof(int));
  char* buf = (char*) malloc(255*sizeof(int));
  printf("(le nom de fichier)\n");
  scanf("%s",nom);
  int fd = open(nom,O_WRONLY|O_TRUNC|O_CREAT, 0666);
  if(fd==-1){
    printf(" create_fichier : fail open \n");
    exit(1);
  }
  for(i=0;i<taille;i++){
    for(j=0;j<taille;j++){
      sprintf(buf,"%d",grille[i][j]);
      r=write(fd,buf,1);
      if(r!=1){
    printf(" probleme de l'ecriture !\n");
    exit(1);
      }
    }
  }
  free(nom);
  free(buf); 
}


/*
    @param: la pointeur de grille,la taille de grille
    @retuen: un fichier qui contient la grille
*/
int** inputFichier(int** grille,int taille){
  int i,j,r;
  char* nom = (char*) malloc(100*sizeof(char));
  char* buf=(char*) malloc(sizeof(char));
  printf("Quel fichier souhaitez-vous ouvrir ?\n");
  scanf("%s",nom);
  int fdin=open(nom,O_RDONLY);
  if(fdin==-1){
    printf(" probleme de lecture !\n");
    exit(1);
  }
  for(i=0;i<taille;i++){
    for(j=0;j<taille;j++){
      r=read(fdin,buf,1);
      if(r!=1){
    printf(" probleme d'initialisation par cet fichier\n");
    exit(1);
      }
      grille[i][j]=atoi(buf);
    }
  }
  free(nom);
  free(buf);
  return grille;
}


/*@require: rien
  @assigns: rien
  @ensure : effacer le flux du input(stdin)
*/
void clearStdin()
{
    while ((getchar()) != '\n');
}



/*
    @param: la pointeur de grille,la taille de grille
    @fun: initialisation la grille selon le client
    @retuen: void 
*/
void initialisation(int** grille,int taille){
    char key;
    printf("Voulez-vous creer la grille avec un fichier existant ? (y/n) \n");
    scanf("%c",&key);
    clearStdin();
    while((key!='y')&&(key!='n'))
    {
      printf("yes or no !? (y/n) \n");
      scanf("%c",&key);
      clearStdin();
    }
    if(key=='y'){
        inputFichier(grille,taille);
    }
    else{
        printf("Donc la grille est aléatoires\n");
        iniGrille(grille,taille);
    }
}





/*
    @param: la pointeur de grille,le couleur d'origine,la taille de grille,coordonneee (x,y),la changement de couleur
    @fun: changer la grille selon le client
    @retuen: void
*/
void traitGrille(int** grille, int taille){
    printf("Quelle couleur choisissez-vous (1-6) ?\n");
    char key;
    scanf("%c",&key);
    clearStdin();
    while((key!='1')&&(key!='2')&&(key!='3')&&(key!='4')&&(key!='5')&&(key!='6'))
    {
      printf("Encore une fois! \n");
      scanf("%c",&key);
      clearStdin();
    }
    int couleur = (int)(key)-48;
    printf("%d\n",couleur );
    initChanger(grille,taille,couleur);

}


/*
    @param: la pointeur de grille,la taille de grille
    @retuen: 1 si le client gagne , 0 sinon
*/
int win(int** grille,int taille){
    int couleur = grille[0][0];
    int i,j;
    for(i=0;i<taille;i++){
        for(j=0;j<taille;j++){
            if(grille[i][j]!=couleur)
                return 0;
        }
    }
    return 1;
}



/*
    @param: la pointeur de grille
    @fun: le procedure de ce jeu. 
    @retuen: void
*/
void game(int** grille,int taille){
    int tour; 
    char tours[3];
    char* p=tours;
    char** endptr=(char**)calloc(10,sizeof(char*));
    printf("Combien de tour  pour gagner ? (Taper un chiffre > 1)\n");
    scanf("%s",p);
    clearStdin();
    tour=strtol(p,endptr,10);
    while((!isnumber(p))||(tour==1))
    {
        printf("Taper un chiffre > 1  \n");
        scanf("%s",p);
        clearStdin();
        tour=strtol(p,endptr,10);
    }
    tour=strtol(p,endptr,10);

    printf("C'est la grille pour vous \n");

    afficher(grille,taille);
    printf("Vas-y !! \n");
    while((tour>0)&&(win(grille,taille)==0)){
        printf("le tour reste : %d \n",tour);
        traitGrille(grille,taille);
        afficher(grille,taille);
        tour--;
    }
    if(tour>0)
        printf("Win \n");
    else
        printf("Vous etes nulle  \n");
    free(endptr);
}



/*
    @param: rien
    @retuen: obtenir la taille de grille selon le client
*/
int getTaille(){
    int taille; 
    char tailles[3];
    char* p=tailles;
    char** endptr=(char**)calloc(10,sizeof(char*));
    printf("choisissez la taille de la grille (6, 12, 18 ou 24)\n");
    scanf("%s",p);
    clearStdin();
    taille=strtol(p,endptr,10);
    while((taille!=6)&&(taille!=12)&&(taille!=18)&&(taille!=24))
    {
        printf("Taper un chiffre (6, 12, 18 ou 24) \n");
        scanf("%s",p);
        clearStdin();
        taille=strtol(p,endptr,10);
    }
    taille=strtol(p,endptr,10);
    free(endptr);
    return taille;
}


int main()
{
    int taille = getTaille();
    
    int** grille = newGrille(taille);
    
    initialisation(grille,taille);

    game(grille,taille);

    freeGrille(grille,taille);
    

    return 0;
}
