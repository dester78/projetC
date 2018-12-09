#ifndef SDLMAIN
#define SDLMAIN

#include <structures.h>
#include <SDLConfigStructures.h>
#include <SDLObjectsStructures.h>

#include <SDL.h>
#include <mysql.h>



    int SDLMainMenuLoop(SDL_Window  *mainWindow,SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files **arrayFiles);

    //Fonction modifiant un tableau en y intégrant les différents modes d'affichage disponibles sur l'écran 1 de l'utilisteur, elle retourne le nombre de mode disponibles
    int SDLGetArrayDisplayModes(SDL_DisplayMode **arrayDisplayModes);

    SDL_Color SDLchangeRGBColor(Uint8 r, Uint8 g, Uint8 b , Uint8 a );

    void buttonHoverEffect(SDL_Renderer *mainRenderer, SDLButtons* button, SDL_Color buttonColor);
    
    void SDLAnimateBackgroundHostMenu( SDL_Texture *texture, SDL_Color newColor );
    void cercle(Uint32 *pixel, int cx, int cy, int rayon,int wTexture, int hTexture, Uint32 pixelColor);
    void controlPixelPosition(Uint32 *pixel, int xPixel, int yPixel, int wTexture, int hTexture, Uint32 pixelColor);
    
#endif