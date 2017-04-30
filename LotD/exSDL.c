
#include <SDL/SDL.h>

/*
 compilation soous Linux : gcc -o exSDL exSDL.c -lSDL
 compilation sur Mac : gcc -o exSDL -I/Library/Frameworks/SDL.framework/Headers  exSDL.c SDLmain.m -framework SDL -framework Cocoa
*/

int autoDraw=0;

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

int main(int argc, char *argv[]) {
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
    ecran=SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("exemple SDL", NULL);
    
    fillScreen(ecran, 0,0,0);
    
    while (continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN: // gestion des évènements clavier
            	switch (event.key.keysym.sym) {
            		case SDLK_d:
                        drawRectangle(ecran, 3, 300, 30, 255, 0, 0);
                        drawRectangle(ecran, 36, 300, 30, 0, 255, 0);
                        drawRectangle(ecran, 69, 300, 30, 0, 0, 255);
                        // ...
                        break;
            		case SDLK_e:
                        fillScreen(ecran, 255,0,255);
						break;
                    case SDLK_r:
                        fillScreen(ecran, 0,0,0);
                        
                        break;
            		case SDLK_ESCAPE:
						continuer=0; break;
            	}
            	break;
                
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x,y;
                    x = event.button.x ;
                    y = event.button.y ;
                    int bpp = ecran->format->BytesPerPixel;
                    /* Here p is the address to the pixel we want to retrieve */
                    Uint8 *p = (Uint8 *)ecran->pixels + y*ecran->pitch + x*bpp;
                    // should be p[0], p[1], p[2] ...
                    fprintf(stderr,"%d %d -> %d %d %d\n",y, x, p[1], p[2], p[3]);
                    drawRectangle(ecran, 3, 3, 30, p[1], p[2], p[3]);
                    drawRectangle(ecran, 36, 3, 30, p[1], p[2], p[3]);
                    drawRectangle(ecran, 69, 3, 30, p[1], p[2], p[3]);

                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    autoDraw=1;
                    drawRectangle(ecran, event.button.x, event.button.y, 3, 0, 255, 0);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                autoDraw=0;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    //drawRectangle(ecran, event.button.x, event.button.y, 3, 255, 0, 0);
                }
                break;

            case SDL_MOUSEMOTION:
                if (autoDraw)
                    drawRectangle(ecran, event.button.x, event.button.y, 1, 0, 0, 255);
                break;
        }
    }
	SDL_Quit();
    
	return 0;
}
