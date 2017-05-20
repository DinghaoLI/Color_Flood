#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "LotA.h"

/**
\file [LotA.c]
\brief Code des fonctions demandés dans le lot A
\author Monsinjon Nicolas, Li Dinghao, Thiry Maxime, Halimi Yael
**/



int** newGrille(int taille){
    int** grille = (int**)calloc(taille,sizeof(int*));
    int i;
    for(i=0 ; i<taille; i++){
        grille[i]=(int*) calloc(taille,sizeof(int));
    }
    return grille;
}
/**
\fn int** newGrille(int taille)
\brief Fonction qui créer la grille de jeu en allouant la mémoire nécessaire
\param taille La taille souhaitée de la grille
\return La grille nouvellement créée
**/

void freeGrille(int** grille,int taille){
    int i;
    for (i=0;i<taille;i++){
        free((void*)grille[i]);
    }
    free((void*)grille);
}
/**
\fn void freeGrille(int** grille,int taille)
\brief Fonction qui libère la mémoire qui a été allouée pour la création de la grille
\param grille La grille de jeu
\param taille La taille de la grille
\return Cette fonction ne retourne rien
**/

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
/**
\fn void iniGrille(int** grille,int taille)
\brief Fonction qui initialise la grille de jeu avec des valeurs aléatoires.
\param grille La grille de jeu
\param taille La taille de la grille
\return Cette fonction ne retourne rien
**/

void createFichier(int** grille,int taille, char* nom){
  int i,j,r;
  char* buf = (char*) malloc(255*sizeof(int));
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
  free(buf);
}
/**
\fn void createFichier(int** grille,int taille, char* nom)
\brief Fonction qui crée un fichier et met les valeurs souhaitées de la grille dedans.
\param grille La grille de jeu
\param taille La taille de la grille
\param nom Le nom que l'on donne au nouveau fichier
\return Cette fonction ne retourne rien
**/
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
/**
\fn int** inputFichier(int** grille,int taille, char* nom)
\brief Fonction qui demande un fichier à ouvrir et qui ensuite initialise la grille de jeu avec les valeurs contenues dans ce fichier.
\param grille La grille de jeu
\param taille La taille de la grille
\param nom Le nom du fichier que l'on veut utiliser
\return La grille initialisée grâce au fichier
**/

void rempalcer (int** grille, int taille, int x, int y, int color){
    if(x>=taille||y>=taille){
        printf("Wrong coordonnee");
    }
    else{
        grille[x][y]=color;
    }
}
/**
\fn void rempalcer (int** grille, int taille, int x, int y, int color)
\brief Fonction qui remplace la couleur de la case de coordonnée (x,y) par la couleur passée en argument
\param grille La grille de jeu
\param taille La taille de la grille
\param x,y les coordonnées de la case dont on veut modifier la couleur
\param color La couleur que l'on veut donner à la case
\return Cette fonction ne retourne rien
**/
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
/**
\fn void changer(int** grille,int colorOrigin, int taille, int x, int y,int color)
\brief Fonction qui remplace la couleur de la case de coordonnée (x,y) par la couleur passée en argument
\param grille La grille de jeu
\param colorOrigin La couleur de la case
\param taille La taille de la grille
\param x,y les coordonnées de la case dont on veut modifier la couleur
\param color La couleur que l'on veut donner à chaque case
\return Cette fonction ne retourne rien
**/

void initChanger(int** grille, int taille, int color){
    int colorOrigin = grille[0][0];
    grille[0][0]=color;
    changer(grille,colorOrigin,taille,0,1,color);
    changer(grille,colorOrigin,taille,1,0,color);
}









/**
\fn void initChanger(int** grille, int taille, int color)
\brief Fonction qui change la couleur des cases de coordonnées (1,0) et (0,1)
\param grille La grille de jeu
\param taille La taille de la grille
\param color La couleur que l'on veut donner à la case
\return Cette fonction ne retourne rien
**/

int testCouleur(int** grille, int taille){
  int i,j;
  int color = grille[0][0];
  for (i=0;i<taille;i++){
    for (j=0;j<taille;j++){
      if (grille[i][j] != color)
        return 0;
    }
  }
  return 1;
}
/**
\fn int testCouleur(int** grille, int taille)
\brief Fonction qui teste si toutes les cases de la grille ont la même valeur
\param grille La grille de jeu
\param taille La taille de la grille
\return 1 si toutes les cases ont la même valeur et 0 sinon
**/
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

