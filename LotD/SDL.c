
#include <SDL/SDL.h>
#include "LotA.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int autoDraw=0;

/*@require: rien
  @assigns: rien
  @ensure : effacer le flux du input(stdin)
*/
void clearStdin()
{
    while ((getchar()) != '\n');
}


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



// px, py coordonnées haut, gauche du pixel
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x=px;
    rect.y=py;
    rect.h=rect.w=size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

/*@require: int i, pointeur rgb
  @assigns: rien
  @ensure : changer chiffre a la valeur rgb
*/
void itoRGB(int i,int* rgb){
    switch(i){
        case 1:
         rgb[0]=255;
         rgb[1]=0;
         rgb[2]=0;
         break;

        case 2:
         rgb[0]=0;
         rgb[1]=255;
         rgb[2]=0;
         break;

         case 3:
         rgb[0]=0;
         rgb[1]=0;
         rgb[2]=255;
         break;

         case 4:
         rgb[0]=255;
         rgb[1]=255;
         rgb[2]=0;
         break;

         case 5:
         rgb[0]=255;
         rgb[1]=0;
         rgb[2]=255;
         break;

         case 6:
         rgb[0]=0;
         rgb[1]=255;
         rgb[2]=255;
         break;

         default:
         rgb[0]=255;
         rgb[1]=255;
         rgb[2]=255;
    }
}

/*@require: pointeur rgb
  @assigns: rien
  @ensure : retourner un chiffre qui represente valeur rgb
*/
int RGBtoi(Uint8* rgb){
    if((rgb[2]==255)&&(rgb[1]==0)&&(rgb[0]==0)){
        return 1;
    }else if((rgb[2]==0)&&(rgb[1]==255)&&(rgb[0]==0)){
        return 2;
    }else if((rgb[2]==0)&&(rgb[1]==0)&&(rgb[0]==255)){
        return 3;
    }else if((rgb[2]==255)&&(rgb[1]==255)&&(rgb[0]==0)){
        return 4;
    }else if((rgb[2]==255)&&(rgb[1]==0)&&(rgb[0]==255)){
        return 5;
    }else if((rgb[2]==0)&&(rgb[1]==255)&&(rgb[0]==255)){
        return 6;
    }
    else{
        return 1;
    }
}

/*@require: pointeur ecran, pointeur grille, int taille
  @assigns: rien
  @ensure : affichage de grille sur SDL
*/
void drawGrille(SDL_Surface *ecran, int** grille, int taille){
    int i,j;
    int rgb[3];
    for(i=0;i<taille;i++){
        for (j=0;j<taille;j++)
        {
            itoRGB(grille[i][j],rgb);
            drawRectangle(ecran, 3+j*30, 3+i*30, 30, rgb[0], rgb[1], rgb[2]);
        }
    }
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



int main(){
	
    // initialisation de la grille
    
    int taille = getTaille();
    int** grille = newGrille(taille);
    initialisation(grille,taille);
    //afficher(grille,taille);
    //copie  pour le solveur
    int** grilleS = newGrille(taille);
    int i,j;
    for(i=0;i<taille;i++){
        for(j=0;j<taille;j++){
            grilleS[i][j]=grille[i][j];
        }
    }

  
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
    printf("Cliquer sur le grille pour changer la couleur \n");


    int continuer = 1;
    SDL_Surface *ecran = NULL;
    SDL_Event event;
    const SDL_VideoInfo* info = NULL;
    SDL_Surface *ima=NULL;
    
    // initialisation de la fenêtre d'affichage
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        /* Failed, exit. */
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        SDL_Quit( );
    }
    info = SDL_GetVideoInfo( );
    if( !info ) {
        /* This should probably never happen. */
        fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
        SDL_Quit( );
    }
    ecran=SDL_SetVideoMode(taille*31, taille*31, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Grille", NULL);
    fillScreen(ecran, 0,0,0);

    drawGrille(ecran,grille,taille);
    while (continuer) {
        
        if(win(grille,taille)){
             printf("Tu gagnes\n");
             break;
        }   

        if(tour==0){
            printf("Tu es perdu\n");
            break;
        }

        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x,y;
                    x = event.button.x ;
                    y = event.button.y ;
                    int bpp = ecran->format->BytesPerPixel;
                    int couleur;
                    /* Here p is the address to the pixel we want to retrieve */
                    Uint8 *p = (Uint8 *)ecran->pixels + y*ecran->pitch + x*bpp;
                    // should be p[0], p[1], p[2] ...
                    // fprintf(stderr,"%d %d -> %d %d %d\n",y, x, p[1], p[2], p[3]);
                    couleur = RGBtoi(p);
                    //fprintf(stderr,"%d %d -> %d %d %d -> %d\n",y, x, p[0], p[1], p[2],couleur);
                    initChanger(grille,taille,couleur);
                    drawGrille(ecran,grille,taille);
                    tour--;
                    printf("le tour reste : %d \n",tour);
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    autoDraw=1;
                    //drawRectangle(ecran, event.button.x, event.button.y, 3, 0, 255, 0);
                }
                break;
            case SDL_MOUSEMOTION:
                if (autoDraw)
                    //drawRectangle(ecran, event.button.x, event.button.y, 1, 0, 0, 255);
                break;
        }
    }

    printf("vous voulez savoir le solveur ?\n");
    printf("le solveur \n");
    //
    //ici, ajouter le solveur sur la grille: grilleS avec taille: taille.
    //afficher(grilleS,taille);
    //
    //
    //solveur(grilleS,taille);
	//
    //

    freeGrille(grille,taille);
    freeGrille(grilleS,taille);
    SDL_Quit();
	return 0;
}
