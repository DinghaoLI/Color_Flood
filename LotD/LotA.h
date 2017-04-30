#ifndef __TEST_H__  
#define __TEST_H__  

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>  


/*
    @param: la taille de grille
    @retuen: la pointeur de grille
*/
int** newGrille(int taille);

/*
    @param: la pointeur de grille,la taille de grille
    @retuen: rien
*/
void freeGrille(int** grille,int taille);

/*
    @param: la pointeur de grille,la taille de grille
    @retuen: la grille avec l'initialisation à partir de valeurs aléatoires
*/
void iniGrille(int** grille,int taille);

/*
    @param: la pointeur de grille,la taille de grille, coordonneee (x,y), color
    @retuen: la grille apres la changement.
*/
void rempalcer (int** grille, int taille, int x, int y, int color);

/*
    @param: la pointeur de grille,le couleur d'origine,la taille de grille,coordonneee (x,y),la changement de couleur
    @retuen: void
*/
void changer(int** grille,int colorOrigin, int taille, int x, int y,int color);

/*
    @param: la pointeur de grille,la taille de grille,,la changement de couleur
    @retuen: void
*/
void initChanger(int** grille, int taille, int color);



/*
    @param: la pointeur de grille,la taille de grille
    @retuen: un fichier qui contient la grille
*/
void createFichier(int** grille,int taille,char* nom);


/*
    @param: la pointeur de grille,la taille de grille
    @retuen: un fichier qui contient la grille
*/
int** inputFichier(int** grille,int taille,char* nom);


int testCouleur(int** grille, int taille);

void afficher(int** grille,int taille);



#endif