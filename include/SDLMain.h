#ifndef SDLMAIN
#define SDLMAIN

#include <structures.h>
#include <SDLConfigStructures.h>
#include <SDLObjectsStructures.h>

#include <SDL.h>
#include <mysql.h>



    int SDLMainMenuLoop(SDL_Window  **mainWindow,SDL_Renderer **mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files **arrayFiles);

    //Fonction modifiant un tableau en y intégrant les différents modes d'affichage disponibles sur l'écran 1 de l'utilisteur, elle retourne le nombre de mode disponibles
    int SDLGetArrayDisplayModes(SDL_DisplayMode **arrayDisplayModes);

    void buttonHoverEffect(SDL_Renderer **mainRenderer, SDLButtons* button, SDL_Color buttonColor);
    
    //void SDLAnimateBackgroundHostMenu( SDL_Surface **surface, SDL_Color newColor );

    short updateBackgroundMenu(SDL_Renderer **mainRenderer, SDLBackground **backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons ,unsigned short countMetroStation);
    
    SDL_Rect createCropRect(SDL_Rect foregroundRect, SDL_Rect backGroundRect);
     
#endif